/**
 * @file navigation.h
 * @brief Defines robot paths and strategies for each task.
 */

#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <FEH.h>

/**
 * @brief Hits the starting button at the beginning of the course.
 *
 * @param rev Reverses the direction of motion when rev = -1.
 */
void hitButton(int rev = 1);

/**
 * @brief Handles the process of picking up the apple bucket.
 *
 * This assumes that the robot has just completed the hitButton strategy,
 * and so is near the starting area.
 */
void pickUpBucket();

/**
 * @brief Handles the process of dropping off a bucket.
 *
 * Assumes the robot has just finished the driveUpRamp strategy,
 * and is positioned at the top level of the ramp.
 */
void dropOffBucket();

/**
 * @brief Drives the robot up the ramp.
 *
 * Assumes the robot has just finished the pickUpButton strategy, and is positioned
 * close to the start of the ramp and motors AB are facing the ramp.
 *
 * @param rev Reverses the direction of motion when rev = -1.
 */
void driveUpRamp(int rev = 1);

/**
 * @brief Flips the appropriate fertilizer lever up or down, adjusting
 * position based on the correct lever.
 *
 * Asssumes the robot has just finished the dropOffBucket strategy,
 * and is positioned near the crate.
 *
 */
void flipFertilizer();

void spinCompost();
void spinComposterSlow();
#endif // NAVIGATION_H
