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

/**
 * @class Drive
 * @brief Controls the movement of a three-motor robot with built-in drift correction
 */
class Drive
{

private:
    Motor &motor1; /**< Reference to motor A */
    Motor &motor2; /**< Reference to motor B */
    Motor &motor3; /**< Reference to motor C */

public:
    enum class DriveMode
    {
        DISTANCE,
        LIGHT
    };

    /**
     * @brief Controls the robot's drive system with a specified mode, direction, power, and optional distance.
     *
     * @param mode The driving mode to use (e.g., tank drive, arcade drive, etc.).
     * @param direction The direction in which the robot should move (e.g., forward, backward, etc.).
     * @param power The power level to apply to the motors (range: 0 to 100).
     * @param distance The distance the robot should travel, in inches. 0 if in light mode.
     */
    void driveWithMode(DriveMode mode, Direction direction, int power, float distance, float timeOut);

    /**
     * @brief Constructs a Drive object with the provided motors
     * @param m1 Reference to motor A
     * @param m2 Reference to motor B
     * @param m3 Reference to motor C
     */
    Drive(Motor &m1, Motor &m2, Motor &m3);

    /**
     * @brief Drives the robot in a specified direction for a given distance
     * @param distance Distance to travel in inches
     * @param direction Direction to travel (enum Direction)
     * @param power Motor power level to use
     */
    void driveDirection(float distance, Direction direction, int power = NORMAL_POWER, float timeOut = 10.0);

    /**
     * @brief Drives the robot in a specified direction until a light is detected.
     *
     * This function moves the robot in the given direction at the specified power
     * level until a light is detected by the robot's sensors. The default power
     * level is set to NORMAL_POWER if not provided.
     *
     * @param direction The direction in which the robot should move.
     *                  This is typically an enumerated type representing directions (e.g., AB, BC).
     * @param power The power level at which the robot should drive.
     *              Defaults to NORMAL_POWER if not specified.
     */
    void driveUntilLight(Direction direction, int power = NORMAL_POWER, float timeOut = 10.0);

    /**
     * @brief Turns the robot clockwise by a specified angle
     * @param degrees Angle to turn in degrees, negative for counterclockwise
     * @param power Motor power level to use during the turn
     */
    void turn(float degrees, int power = NORMAL_POWER);
};

#endif // DRIVE_H
