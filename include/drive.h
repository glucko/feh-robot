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
    float x;     // X coordinate in inches
    float y;     // Y coordinate in inches
    float theta; // Orientation in radians
};

// Robot pose structure
struct RobotPose
{
    float x;     // X position in inches
    float y;     // Y position in inches
    float theta; // Orientation in radians
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
    float wheelAngles[3]; // Angle of each wheel in radians

    // Previous encoder counts for odometry
    int prevCounts[3];

    // Odometry and control functions
    void updateOdometry();
    void calculateWheelVelocities(float vx, float vy, float omega, float velocities[3]);
    void resetPose();

public:
    Drive();
    void driveToPosition(Waypoint point, int power);
};

#endif // DRIVE_H
