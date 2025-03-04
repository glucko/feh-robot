#ifndef UTILITIES_H
#define UTILITIES_H

#include "include/logger.h"

// Logger
extern Logger logger;

// Function declarations
void waitUntilTouch();
int inchesToCounts(float inches);
float degToRad(float deg); // Change return type to float for correct conversion
void resetAll();

#endif // UTILITIES_H
