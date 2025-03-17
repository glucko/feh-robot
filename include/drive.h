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

#include <FEHIO.h>
#include "motor.h"
#include "constants.h"
#include "MiniPID.h"

/**
 * @class Drive
 * @brief Controls the movement of a three-motor robot with built-in drift correction
 */
class Drive
{

private:
    float kP; /**< Proportional correction factor for straight-line driving */

    Motor &motor1; /**< Reference to motor A */

    Motor &motor2; /**< Reference to motor B */

    Motor &motor3; /**< Reference to motor C */

    MiniPID pid; /**< The PID system */

    /**
     * @brief Applies correction to keep the robot driving straight
     * @param mot1 Pointer to the first motor currently driving
     * @param mot2 Pointer to the second motor currently driving
     * @param targetPower The desired power setting to maintain
     */
    void correctDriveStraight(Motor *mot1, Motor *mot2, int targetPower);

public:
    /**
     * @brief Constructs a Drive object with the provided motors
     * @param m1 Reference to motor A
     * @param m2 Reference to motor B
     * @param m3 Reference to motor C
     * @param correctionFactor Controls the aggressiveness of the straight-line correction (higher is more aggressive)
     */
    Drive(Motor &m1, Motor &m2, Motor &m3, float correctionFactor = 0.5);

    /**
     * @brief Drives the robot in a specified direction for a given distance
     * @param distance Distance to travel in inches
     * @param direction Direction to travel (enum Direction)
     * @param power Motor power level to use
     */
    void driveDirection(float distance, Direction direction, int power = NORMAL_POWER);

    void driveUntilLight(Direction direction, int power = NORMAL_POWER);

    /**
     * @brief Turns the robot by a specified angle
     * @param degrees Angle to turn in degrees
     * @param clockwise True for clockwise rotation, false for counter-clockwise
     * @param power Motor power level to use during the turn
     */
    void turn(float degrees, bool clockwise = true, int power = NORMAL_POWER);
};

#endif // DRIVE_H
