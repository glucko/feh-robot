#include <math.h>
#include <FEHLCD.h>
#include "include/utils.h"
#include "include/constants.h"
#include "include/logger.h"
#include "include/motor.h"

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

int inchesToCounts(float inches)
{
    return static_cast<int>(inches * COUNTS_PER_ENCODER / M_PI * WHEEL_DIAMETER);
}

float degToRad(float deg)
{
    return deg * M_PI / 180;
}

void resetAll()
{
    motorA.stopAndReset();
    motorB.stopAndReset();
    motorC.stopAndReset();
}
