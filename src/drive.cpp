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

    // Define the ramp location (example values - adjust to your course)
    ramp.startX = 60.0;
    ramp.startY = 24.0;
    ramp.endX = 72.0;
    ramp.endY = 36.0;
    ramp.width = 15.0;
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

    // Calculate change in encoder counts
    float deltaCounts[3] = {
        static_cast<float>(currentCounts[0] - prevCounts[0]),
        static_cast<float>(currentCounts[1] - prevCounts[1]),
        static_cast<float>(currentCounts[2] - prevCounts[2])};

    // Convert encoder counts to wheel distances (inches)
    float wheelDistances[3] = {
        countsToInches(deltaCounts[0]),
        countsToInches(deltaCounts[1]),
        countsToInches(deltaCounts[2])};

    // Calculate robot motion in local frame
    float localMotion[3] = {0, 0, 0}; // [dx, dy, dtheta]

    // For each wheel, contribute its motion to overall robot motion
    for (int i = 0; i < 3; i++)
    {
        // Wheel contribution to X motion
        localMotion[0] += wheelDistances[i] * cos(wheelAngles[i]);

        // Wheel contribution to Y motion
        localMotion[1] += wheelDistances[i] * sin(wheelAngles[i]);

        // Wheel contribution to rotation
        localMotion[2] += wheelDistances[i] / ROBOT_DIAMETER / 2.0;
    }

    // Normalize by number of wheels
    localMotion[0] /= 3.0;
    localMotion[1] /= 3.0;
    localMotion[2] /= 3.0;

    // Convert local motion to global motion based on current orientation
    float cosTheta = cos(pose.theta);
    float sinTheta = sin(pose.theta);

    float globalDx = localMotion[0] * cosTheta - localMotion[1] * sinTheta;
    float globalDy = localMotion[0] * sinTheta + localMotion[1] * cosTheta;

    // Update robot pose
    pose.x += globalDx;
    pose.y += globalDy;
    pose.theta += localMotion[2];

    // Normalize theta to -pi to pi
    pose.theta = atan2(sin(pose.theta), cos(pose.theta));

    // Update previous counts for next iteration
    for (int i = 0; i < 3; i++)
    {
        prevCounts[i] = currentCounts[i];
    }
}

// Calculate required wheel velocities for desired robot motion
void Drive::calculateWheelVelocities(float vx, float vy, float omega, float velocities[3])
{
    for (int i = 0; i < 3; i++)
    {
        // Calculate wheel velocity based on desired robot motion
        velocities[i] = vx * cos(wheelAngles[i]) +
                        vy * sin(wheelAngles[i]) +
                        omega * ROBOT_DIAMETER / 2.0;
    }
}

// Drive to a specific position with automatic ramp handling
void Drive::driveToPosition(Waypoint target, int basePower)
{
    // Constants for position thresholds
    const float POS_THRESHOLD = 0.5;           // 0.5 inches
    const float ANGLE_THRESHOLD = degToRad(1); // 1 degree

    // if on ramp, set pid differently
    double encoderXError, encoderYError, encoderThetaError;
    double outputX, outputY, outputTheta;
    double PIDTarget = 0.0;

    PID pidX = PID(&encoderXError, &outputX, &PIDTarget, .5, 0, 0, DIRECT);
    PID pidY = PID(&encoderYError, &outputY, &PIDTarget, .5, 0, 0, DIRECT);
    PID pidTheta = PID(&encoderThetaError, &outputTheta, &PIDTarget, .5, 0, 0, DIRECT);

    pidX.SetOutputLimits(-200, 200);
    pidY.SetOutputLimits(-200, 200);
    pidTheta.SetOutputLimits(-200, 200);

    pidX.SetMode(AUTOMATIC);
    pidY.SetMode(AUTOMATIC);
    pidTheta.SetMode(AUTOMATIC);

    // Main control loop
    bool reachedTarget = false;
    while (!reachedTarget)
    {
        // Update current position
        updateOdometry();

        // Calculate error between current and target position
        float errorX = target.x - pose.x;
        float errorY = target.y - pose.y;

        // Convert errors to local robot frame
        float cosTheta = cos(pose.theta);
        float sinTheta = sin(pose.theta);

        // how far the robot is from the point
        encoderXError = errorX * cosTheta + errorY * sinTheta;
        encoderYError = -errorX * sinTheta + errorY * cosTheta;

        // Calculate error in orientation (normalized to -π to π)
        encoderThetaError = target.theta - pose.theta;
        encoderThetaError = atan2(sin(encoderThetaError), cos(encoderThetaError));

        // Compute PID outputs
        pidX.Compute();
        pidY.Compute();
        pidTheta.Compute();

        // Calculate wheel velocities for the desired motion
        float velocities[3];
        if (isnan(outputY))
        {
            outputY = 0;
        }

        if (isnan(outputTheta))
        {
            outputTheta = 0;
        }

        calculateWheelVelocities(outputX, outputY, outputTheta, velocities);

        // Set wheel speeds
        String test1 = String(outputX) + " " + String(outputY) + " " + String(outputTheta);
        logger.log(test1);

        String test = String(velocities[0]) + " " + String(velocities[1]) + " " + String(velocities[2]);
        logger.log(test);

        motorA.SetPercent(velocities[0]);
        motorB.SetPercent(velocities[1]);
        motorC.SetPercent(velocities[2]);

        // Check if we've reached the target
        reachedTarget = (fabs(outputX) < POS_THRESHOLD &&
                         fabs(outputY) < POS_THRESHOLD &&
                         fabs(outputTheta) < ANGLE_THRESHOLD);

        Sleep(.1);
    }

    resetAll();
}