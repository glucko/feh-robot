#include <FEH.h>
#include "utils.h"
#include "constants.h"
#include "motor.h"

Logger logger = Logger();

void waitUntilTouch()
{
    int left;
    int right;

    while (!LCD.Touch(&left, &right))
    {
    }

    while (LCD.Touch(&left, &right))
    {
    }
}

int inchesToCounts(float inches)
{
    return static_cast<int>(inches * (COUNTS_PER_ENCODER / (M_PI * WHEEL_DIAMETER)));
}

float countsToInches(int counts)
{
    return counts / (COUNTS_PER_ENCODER / (M_PI * WHEEL_DIAMETER));
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

int getHumidifierLight()
{
    float val = cdsCell.Value();

    if (val > noLightThreshold)
    {
        logger.log("No light detected");
        return -1;
    }

    if (val <= redThreshold)
    {
        logger.log("Red light detected");
        return 0;
    }

    logger.log("Blue light detected");
    return 1;
}