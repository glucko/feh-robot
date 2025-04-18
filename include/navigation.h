/**
 * @file navigation.h
 * @brief Defines robot paths and strategies for each task.
 */

#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <FEH.h>

void hitStartButton();

void driveToBucket();
void pickUpBucket();

void dropOffBucket();

void driveToRampFromBucket();
void driveUpRampAndRealign();

void driveToFertilizerFromTable();
void flipFertilizerDown();

void hitButton();
void fertilizerFromButton();

void goToWindowFromButton();
void pushWindow();

void driveToCompostFromWindow();
void spinCompost();
void hitButtonFromCompost();

#endif // NAVIGATION_H
