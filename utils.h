#ifndef UTILITIES_H
#define UTILITIES_H

#include <math.h>
#include "constants.h"

// Function declarations
int inchesToCounts(float inches);
float degToRad(float deg); // Change return type to float for correct conversion
void stopMotors();
void resetEncoders();

#endif // UTILITIES_H
