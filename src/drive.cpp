#include <FEH.h>
#include <PID_v1.h>
#include <math.h>
#include "drive.h"
#include "utils.h"
#include "constants.h"

// Sleep time between drive operations
const double SLEEPTIME = 0.5;

Drive::Drive()
{
    // Initialize robot pose
    pose.x = 0;
    pose.y = 0;
    pose.theta = 0;

    // Initialize wheel positions (120 degrees apart)
    wheelAngles[0] = 0;            // Motor 1 at 0 degrees
    wheelAngles[1] = 2 * M_PI / 3; // Motor 2 at 120 degrees
    wheelAngles[2] = 4 * M_PI / 3; // Motor 3 at 240 degrees

    // Initialize previous encoder counts
    prevCounts[0] = 0;
    prevCounts[1] = 0;
    prevCounts[2] = 0;

    // Initialize motor directions
    motorDirections[0] = 1;
    motorDirections[1] = 1;
    motorDirections[2] = 1;
}

// Reset pose to origin
void Drive::resetPose()
{
    pose.x = 0;
    pose.y = 0;
    pose.theta = 0;
}

// Update the robot's position based on encoder readings
void Drive::updateOdometry()
{
    // Get current encoder counts
    int currentCounts[3] = {
        motorA.Counts(),
        motorB.Counts(),
        motorC.Counts()};

    // Calculate change in encoder counts and update previous counts
    int deltaCounts[3];
    for (int i = 0; i < 3; i++)
    {
        deltaCounts[i] = motorDirections[i] * (currentCounts[i] - prevCounts[i]);
        prevCounts[i] = currentCounts[i];
    }

    // Calculate change in distance
    double deltaX = 0, deltaY = 0, deltaTheta = 0;
    for (int i = 0; i < 3; i++)
    {
        // Wheel contribution to X motion
        deltaX += countsToInches(deltaCounts[i]) * cos(wheelAngles[i]);
        deltaY += countsToInches(deltaCounts[i]) * sin(wheelAngles[i]);
        deltaTheta += countsToInches(deltaCounts[i]) / ROBOT_DIAMETER / 2.0;
    }

    // Update robot pose
    pose.x += deltaX;
    pose.y += deltaY;
    pose.theta += deltaTheta;

    // Normalize theta to -pi to pi
    pose.theta = atan2(sin(pose.theta), cos(pose.theta));
}

double mapf(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Then modify your driveToPosition function to prioritize movement over rotation
void Drive::driveToPosition(Waypoint target, int basePower)
{
    updateOdometry();
    resetMotors();

    const double POS_THRESHOLD = 1;

    double vx = 0;
    double vy = 0;
    double xSetpoint = target.x;
    double ySetpoint = target.y;

    PID xPID = PID(&pose.x, &vx, &xSetpoint, 4, 0, 0, REVERSE);
    PID yPID = PID(&pose.y, &vy, &ySetpoint, 4, 0, 0, REVERSE);

    xPID.SetOutputLimits(-30, 30);
    yPID.SetOutputLimits(-30, 30);

    xPID.SetMode(AUTOMATIC);
    yPID.SetMode(AUTOMATIC);

    // Inital compute to avoid bad first values
    xPID.Compute();
    yPID.Compute();

    bool reachedTarget = false;
    while (!reachedTarget)
    {
        updateOdometry();

        // do not put these directly in the if because short circuiting will make the pid not evaluate
        bool a = xPID.Compute();
        bool b = yPID.Compute();
        if (!a && !b)
        {
            continue;
        }

        double deadband = 20;
        double vxa = vx;
        double vya = vy;
        if (fabs(vy) > POS_THRESHOLD && fabs(vy) < deadband)
        {
            // Create a smooth curve within the deadband
            double ratio = abs(vy) / deadband; // 0.0 to 1.0
            double sign = (vy >= 0) ? 1.0 : -1.0;

            // Use ratio to smoothly scale from deadband to deadband + small extra push
            vya = sign * (deadband + ratio * 3.0);
        }

        if (fabs(vx) > 1 && fabs(vx) < deadband)
        {
            // Create a smooth curve within the deadband
            double ratio = abs(vx) / deadband; // 0.0 to 1.0
            double sign = (vx >= 0) ? 1.0 : -1.0;

            // Use ratio to smoothly scale from deadband to deadband + small extra push
            vxa = sign * (deadband + ratio * 5.0);
        }

        const double sqrt3o2 = 1.0 * sqrt(3) / 2;
        double v1 = -constrain((-vxa), -30, 30);
        double v2 = -constrain((.5 * vxa + sqrt3o2 * vya), -30, 30);
        double v3 = -constrain((.5 * vxa - sqrt3o2 * vya), -30, 30);

        motorDirections[0] = v1 < 0 ? -1 : 1;
        motorDirections[1] = v2 < 0 ? -1 : 1;
        motorDirections[2] = v3 < 0 ? -1 : 1;

        logger.log("vx: " + String(vx) + " vy: " + String(vy));
        logger.log("vxa: " + String(vxa) + " vya: " + String(vya));
        logger.log("v1: " + String(v1) + " v2: " + String(v2) + " v3: " + String(v3));
        logger.log("target.x: " + String(target.x) + " pose.x: " + String(pose.x));
        logger.log("target.y: " + String(target.y) + " pose.y: " + String(pose.y) + "\n");

        motorA.SetPercent(v1);
        motorB.SetPercent(v2);
        motorC.SetPercent(v3);

        reachedTarget = fabs(vx) < POS_THRESHOLD && fabs(vy) < POS_THRESHOLD;
    }

    resetMotors();
}