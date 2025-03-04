#ifndef UTILITIES_H
#define UTILITIES_H

#include "include/logger.h"

extern Logger logger;

// Stops code execution until Proteus screen is touched
void waitUntilTouch();

// Converts inches to encoder counts based on wheel specifications
int inchesToCounts(float inches);

// Convert degrees to radians
float degToRad(float deg); // Change return type to float for correct conversion

// Stops all motors and resets encoders
void resetAll();

#endif // UTILITIES_H
