/**
 * @file utils.h
 * @brief Utility functions for the FEH robot project.
 *
 * This file contains various utility functions that are used throughout
 * the FEH robot project, including functions for waiting for a touch
 * on the Proteus screen, converting distances and angles, stopping motors,
 * and getting the color of the humidifier light.
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#include "logger.h"
#include "constants.h"

extern Logger logger;

/**
 * @brief Stops code execution until Proteus screen is touched
 */
void waitUntilTouch();

/**
 * @brief Converts distance in inches to encoder counts.
 *
 * @param inches The distance in inches to convert.
 * @return int The equivalent number of encoder counts.
 */
int inchesToCounts(float inches);

/**
 * @brief Converts encoder counts to distance in inches.
 *
 * @param int The equivalent number of encoder counts.
 * @return float The distance in inches to convert.
 */
float countsToInches(float inches);

/**
 * @brief Convert degrees to radians
 *
 * @param deg The angle in degrees
 * @return float The equivalent angle in radians
 */
float degToRad(float deg);

/**
 * @brief Stops all motors and resets encoders
 */
void resetAll();

/**
 * @brief Gets the color of the humidifier light
 *
 * @return the respective enum value for the light.
 */
Light getHumidifierLight();

#endif // UTILITIES_H
