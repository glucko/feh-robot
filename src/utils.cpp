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

void servoLeveling(int currentPosition, int position){
    int leveling = ((position-currentPosition)) / 10;
    float rem = ((position-currentPosition)) % 10;
    int i = 0;
    for(i = 0; i < leveling; i++){
        servo.SetDegree(i*leveling);
        Sleep(.1);
        i++;
    }
    currentPosition = i*leveling+rem;
    servo.SetDegree(currentPosition);
}