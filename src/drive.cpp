#include <FEH.h>
#include <PID_v1.h>
#include <math.h>
#include "drive.h"
#include "utils.h"
#include "constants.h"

// Sleep time between drive operations
const float SLEEPTIME = 0.5;

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
    prevCounts[0] = motorA.Counts();
    prevCounts[1] = motorB.Counts();
    prevCounts[2] = motorC.Counts();

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
    float deltaX = 0, deltaY = 0, deltaTheta = 0;
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

    // logger.log("x: " + String(pose.x) + " y: " + pose.y + " theta: " + pose.theta);

    // Normalize theta to -pi to pi
    pose.theta = atan2(sin(pose.theta), cos(pose.theta));
}

float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Then modify your driveToPosition function to prioritize movement over rotation
void Drive::driveToPosition(Waypoint target, int basePower)
{
    // Constants for position thresholds
    const float POS_THRESHOLD = 0.5;           // 0.5 inches
    const float ANGLE_THRESHOLD = degToRad(2); // Increased to 2 degrees

    // double positionError, orientationError;
    // double outputMagnitude, outputTheta;
    // double PIDTarget = 0.0;

    // // Use two PIDs instead of three - one for distance to target, one for orientation
    // PID pidPosition = PID(&positionError, &outputMagnitude, &PIDTarget, 0.08, 0.001, 0.03, DIRECT);
    // PID pidTheta = PID(&orientationError, &outputTheta, &PIDTarget, 0.02, 0, 0.01, DIRECT);

    // pidPosition.SetOutputLimits(0, 35); // Reduced from 80 to 35
    // pidTheta.SetOutputLimits(-15, 15);  // Reduced from -40,40 to -15,15

    // pidPosition.SetMode(AUTOMATIC);
    // pidTheta.SetMode(AUTOMATIC);

    bool reachedTarget = false;
    while (!reachedTarget)
    {
        updateOdometry();

        // The vector to get to the correct location
        float vx = -(target.x - pose.x);
        float vy = -(target.y - pose.y);

        // TODO: it should somewhat scale off of distance from target, but not too much
        // TODO: implement PID
        // Normalize so speed is independent of how close the robot is to dest
        float magnitude = sqrt(sq(vx) + sq(vy));
        vx = mapf(vx / magnitude, -1, 1, -30, 30);
        vy = mapf(vy / magnitude, -1, 1, -30, 30);

        const float sqrt3o2 = 1.0 * sqrt(3) / 2;
        float v1 = -vx;
        float v2 = .5 * vx - sqrt3o2 * vy;
        float v3 = .5 * vx + sqrt3o2 * vy;

        logger.log("v1: " + String(v1) + " v2: " + String(v2) + " v3: " + String(v3));
        logger.log("pose x: " + String(pose.x) + " pose y: " + String(pose.y) + "\n");

        motorA.SetPercent(v1);
        motorB.SetPercent(v2);
        motorC.SetPercent(v3);

        motorDirections[0] = v1 < 0 ? -1 : 1;
        motorDirections[1] = v2 < 0 ? -1 : 1;
        motorDirections[2] = v3 < 0 ? -1 : 1;

        reachedTarget = fabs(vx) < 1 && fabs(vy) < 1;
        Sleep(0.1);
    }

    resetMotors();
}