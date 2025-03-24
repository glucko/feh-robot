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

extern Logger logger;
/**
 * @brief Clamps a float value between a minimum and maximum range.
 *
 * @param value The value to clamp.
 * @param min The minimum allowable value.
 * @param max The maximum allowable value.
 * @return float The clamped value.
 */
float clamp(float value, float min, float max);

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
 * @return int 0 for red and 1 for blue
 */
int getHumidifierLight();

#endif // UTILITIES_H
