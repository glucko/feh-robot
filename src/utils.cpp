#include <math.h>
#include <FEHLCD.h>
#include "include/utils.h"
#include "include/constants.h"
#include "include/logger.h"

// Initialize Logger
Logger logger = Logger("test.txt");

void waitUntilTouch()
{
    float left;
    float right;

    while (!LCD.Touch(&left, &right))
    {
    }

    while (LCD.Touch(&left, &right))
    {
    }
}

// Function to convert inches to counts based on wheel specifications
int inchesToCounts(float inches)
{
    return static_cast<int>(inches * COUNTS_PER_ENCODER / M_PI * WHEEL_DIAMETER);
}

// Function to convert degrees to radians
float degToRad(float deg) // Change return type to float for correct conversion
{
    return deg * M_PI / 180;
}

// Function to stop all motors
void stopMotors()
{
    motorA.SetPercent(0);
    motorB.SetPercent(0);
    motorC.SetPercent(0);
}

// Function to reset encoder counts
void resetEncoders()
{
    encoderA.ResetCounts();
    encoderB.ResetCounts();
    encoderC.ResetCounts();
}
