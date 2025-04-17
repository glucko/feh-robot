/**
 * @file drive.h
 * @brief Header file for the Drive class, which controls the movement of a three-motor robot with built-in drift correction.
 *
 * This file contains the definition of the Drive class, which provides methods to drive the robot in a specified direction,
 * turn the robot by a specified angle, and apply correction to keep the robot driving straight.
 *
 */

#ifndef DRIVE_H
#define DRIVE_H

#include <FEH.h>
#include "motor.h"
#include "constants.h"

// Define a waypoint structure for path planning
struct Waypoint
{
    double x; // X coordinate in inches
    double y; // Y coordinate in inches
};

// Robot pose structure
struct RobotPose
{
    double x;     // X position in inches
    double y;     // Y position in inches
    double theta; // Orientation in radians
};

/**
 * @class Drive
 * @brief Controls the movement of a three-motor robot with built-in drift correction
 */
class Drive
{

private:
    // Robot pose tracking
    RobotPose pose;

    // Motor directions for odometry
    int motorDirections[3];

    // Wheel configuration
    double wheelAngles[3]; // Angle of each wheel in radians

    // Previous encoder counts for odometry
    int prevCounts[3];

    // Odometry and control functions
    void updateOdometry();
    void calculateWheelVelocities(double vx, double vy, double omega, double velocities[3]);
    void resetPrevCounts();

public:
    Drive();
    void driveToPosition(Waypoint point, int basePower = 25, bool ramp = false);
    void turn(double targetAngle, int basePower = 30);
    void driveUpRamp();
    void driveDownRamp();
};

#endif // DRIVE_H
