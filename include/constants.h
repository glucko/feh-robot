/**
 * @file constants.h
 * @brief Defines constants and global variables used throughout the FEH robot project
 *
 * @note All extern variables declared here must be defined in a corresponding .cpp file
 * @author FEH Robot Team
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <FEHIO.h>
#include <FEHMotor.h>
#include "include/motor.h"

/**
 * @brief The diameter of the circumscribed circle of the robot.
 */
const float ROBOT_DIAMETER = 5;

/**
 * @brief The diameter of the robot's wheels in inches.
 */
const float WHEEL_DIAMETER = 2.5;

/**
 * @brief Motor instance for MotorA.
 *
 * Located between the apple bucket and stick mechanisms, connected to port P0_0.
 */
extern Motor motorA;

/**
 * @brief Motor instance for MotorB.
 *
 * Located between the compost and apple bucket mechanisms, connected to port P0_1.
 */
extern Motor motorB;

/**
 * @brief Motor instance for MotorC.
 *
 * Located between the apple bucket and stick mechanisms connected to port P0_2.
 */
extern Motor motorC;

/**
 * @brief Analog input pin for the CdS cell.
 *
 * Used for humidifier detection and is connected to port P1_1.
 */
extern AnalogInputPin cdsCell;

/**
 * @brief Threshold value for detecting red light.
 *
 * When the CdS cell reading falls below this value, the robot will identify it as red light.
 */
const float redThreshold = .39;

/**
 * @brief Threshold value for detecting absence of light.
 *
 * When the CdS cell reading exceeds this value, the robot will identify it as no light present.
 */
const float noLightThreshold = 1;

/**
 * @brief Number of counts per encoder revolution for the servo motors
 *
 * This constant represents the number of counts registered by the motor encoder
 * for one complete revolution of the shaft. Used for accurate position and
 * movement distance calculations.
 *
 * @note The value of 318 counts is specific to the motor encoders used in the FEH robot
 */
const int COUNTS_PER_ENCODER = 318;

/**
 * @brief The power that should be used for normal operation.
 */
const int NORMAL_POWER = 25;

/**
 * @brief Defines directions that the robot can travel straight in.
 */
enum class Direction
{
    LEFT,
    FORWARD,
    RIGHT
};

#endif
