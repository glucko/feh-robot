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

void Drive::resetPrevCounts()
{
    prevCounts[0] = 0;
    prevCounts[1] = 0;
    prevCounts[2] = 0;
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
        deltaTheta += (countsToInches(deltaCounts[i]) / ROBOT_RADIUS) / 3.0;
    }

    // Update robot pose
    pose.x += deltaX;
    pose.y += deltaY;
    pose.theta += deltaTheta;

    // Normalize theta to -pi to pi
    pose.theta = atan2(sin(pose.theta), cos(pose.theta));
}

void Drive::driveToPosition(Waypoint target, int basePower, bool ramp)
{
    updateOdometry();
    resetMotors();

    const double POS_THRESHOLD = 1;

    double vx = 0;
    double vy = 0;
    double xSetpoint = target.x;
    double ySetpoint = target.y;

    double dpx = 1.56;
    double dpy = 2.08;

    if (ramp)
    {
        dpx *= 2;
        dpy *= 2;
    }

    PID xPID = PID(&pose.x, &vx, &xSetpoint, dpx, .12, .16, REVERSE);
    PID yPID = PID(&pose.y, &vy, &ySetpoint, dpy, .15, .2, DIRECT);

    xPID.SetOutputLimits(-basePower, basePower);
    yPID.SetOutputLimits(-basePower, basePower);

    xPID.SetMode(AUTOMATIC);
    yPID.SetMode(AUTOMATIC);

    // Inital compute to avoid bad first values
    xPID.Compute();
    yPID.Compute();

    // double lastTime = TimeNow();
    bool reachedTarget = false;
    while (!reachedTarget)
    {
        updateOdometry();

        // do not put these directly in the if because short circuiting will make the pid not evaluate
        bool a = xPID.Compute();
        bool b = yPID.Compute();
        if (!a && !b)
        {
            reachedTarget = fabs(vx) < POS_THRESHOLD && fabs(vy) < POS_THRESHOLD;
            continue;
        }

        // double currentTime = TimeNow();
        // double deltaTime = currentTime - lastTime;
        // logger.log("Loop time: " + String(deltaTime) + " s");
        // lastTime = currentTime;

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
        double va = constrain((-vxa), -basePower, basePower);
        double vb = constrain((.5 * vxa + sqrt3o2 * vya), -basePower, basePower);
        double vc = constrain((.5 * vxa - sqrt3o2 * vya), -basePower, basePower);

        motorDirections[0] = va < 0 ? -1 : 1;
        motorDirections[1] = vb < 0 ? -1 : 1;
        motorDirections[2] = vc < 0 ? -1 : 1;

        // This code significantly slows down the loop
        //  logger.log("vx: " + String(vx) + " vy: " + String(vy) +
        //             "\nvxa: " + String(vxa) + " vya: " + String(vya) +
        //             "\nv1: " + String(va) + " v2: " + String(vb) + " v3: " + String(vc) +
        //             "\ntarget: (" + String(target.x) + "," + String(target.y) +
        //             ")\npose: (" + String(pose.x) + "," + String(pose.y) + ")\n");

        motorA.SetPercent(va);
        motorB.SetPercent(vb);
        motorC.SetPercent(vc);

        reachedTarget = fabs(vx) < POS_THRESHOLD && fabs(vy) < POS_THRESHOLD;
    }

    resetMotors();
    resetPrevCounts();
}

void Drive::turn(double targetAngle, int basePower)
{
    targetAngle = targetAngle * DEG_TO_RAD;
    updateOdometry();
    resetMotors();

    const double THRESHOLD = 1 * DEG_TO_RAD;

    // Normalize target angle to -pi to pi
    targetAngle = atan2(sin(targetAngle), cos(targetAngle));

    // PID for angular control
    double vtheta = 0;
    double rotationSetpoint = targetAngle;
    PID rotationPID = PID(&pose.theta, &vtheta, &rotationSetpoint, 3.0, 0.1, 0.2, DIRECT);

    rotationPID.SetOutputLimits(-basePower, basePower);
    rotationPID.SetMode(AUTOMATIC);

    // Initial compute to avoid bad first values
    rotationPID.Compute();

    bool reachedAngle = false;
    double prevOutput = 0;
    while (!reachedAngle)
    {
        updateOdometry();

        // Fix the setpoint to handle wraparound between -pi and pi
        double angleDiff = targetAngle - pose.theta;
        // Normalize the angle difference to [-pi, pi]
        angleDiff = atan2(sin(angleDiff), cos(angleDiff));
        rotationSetpoint = pose.theta + angleDiff;

        if (!rotationPID.Compute())
        {
            reachedAngle = fabs(angleDiff) < THRESHOLD;
            continue;
        }

        // Smooth sudden changes in output
        double alpha = 0.3; // Smoothing factor (0-1)
        double rotationOutput = alpha * vtheta + (1 - alpha) * prevOutput;
        prevOutput = rotationOutput;

        // Apply minimum power if we're very close but not quite there
        double minPower = 20;
        if (fabs(rotationOutput) < minPower && fabs(rotationOutput) > THRESHOLD)
        {
            double sign = (rotationOutput > 0) ? 1.0 : -1.0;
            rotationOutput = sign * minPower; // Minimum power to overcome static friction
        }

        // Calculate motor powers for pure rotation movement
        double motorPower = rotationOutput;

        motorDirections[0] = motorPower < 0 ? -1 : 1;
        motorDirections[1] = motorPower < 0 ? -1 : 1;
        motorDirections[2] = motorPower < 0 ? -1 : 1;

        motorA.SetPercent(motorPower);
        motorB.SetPercent(motorPower);
        motorC.SetPercent(motorPower);

        // logger.log("vtheta: " + String(vtheta) +
        //            "\noutput: " + String(rotationOutput) +
        //            "\ndiff: " + String(angleDiff) +
        //            "\ntarget: " + String(targetAngle) +
        //            ")\npose: " + String(pose.theta) + "\n");

        // Check if the angle difference is small enough
        reachedAngle = fabs(angleDiff) < THRESHOLD;
    }

    resetMotors();
    resetPrevCounts();
}
