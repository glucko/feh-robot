#ifndef UTILITIES_H
#define UTILITIES_H

// Logger
Logger logger;

// Function declarations
int inchesToCounts(float inches);
float degToRad(float deg); // Change return type to float for correct conversion
void stopMotors();
void resetEncoders();

#endif // UTILITIES_H
