/**
 * @file navigation.h
 * @brief Defines robot paths and strategies for each task.
 */

#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <FEH.h>

void hitButton();

void driveToBucket();
void pickUpBucket();

void dropOffBucket();

void driveToRampFromBucket();
void driveUpRampAndRealign();

void driveToFertilizerFromTable();
void flipFertilizerDown();

void hitButton();

void goToWindowFromButton();
void pushWindow();

void driveToCompostFromWindow();
void spinCompost();
void hitButtonFromCompost();

#endif // NAVIGATION_H
