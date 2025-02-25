#include <math.h>
#include "constants.h"

int inchesToCounts(float inches)
{
    return inches * COUNTS_PER_ENCODER / M_PI * WHEEL_DIAMETER;
}

int degToRad(float deg)
{
    return deg * M_PI / 180;
}

void stopMotors()
{
    motorA.SetPercent(0);
    motorB.SetPercent(0);
    motorC.SetPercent(0);
}

void resetEncoders()
{
    encoderA.ResetCounts();
    encoderB.ResetCounts();
    encoderC.ResetCounts();
}