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

float countsToInches(float counts)
{
    return counts / (COUNTS_PER_ENCODER / (M_PI * WHEEL_DIAMETER));
}

float degToRad(float deg)
{
    return deg * M_PI / 180;
}

void resetMotors()
{
    motorA.stopAndReset();
    motorB.stopAndReset();
    motorC.stopAndReset();
}

Light getHumidifierLight()
{
    float val = cdsCell.Value();

    if (val > noLightThreshold)
    {
        logger.log("No light detected");
        return Light::NOLIGHT;
    }

    if (val <= redThreshold)
    {
        logger.log("Red light detected");
        return Light::NOLIGHT;
    }

    logger.log("Blue light detected");
    return Light::BLUELIGHT;
}

int currentPosition = 0;

void servoLeveling(int targetPosition)
{
    int step = 10;
    while (currentPosition != targetPosition)
    {
        if (abs(targetPosition - currentPosition) < step)
        {
            currentPosition += (targetPosition - currentPosition);
        }
        else if (targetPosition > currentPosition)
        {
            currentPosition += step;
        }
        else
        {
            currentPosition -= step;
        }

        currentPosition = constrain(currentPosition, 0, 180);
        servo.SetDegree(currentPosition);
        Sleep(0.1);
    }

    currentPosition = targetPosition;
    servo.SetDegree(targetPosition);
}
