#include <FEH.h>
#include "constants.h"
#include "utils.h"
#include "navigation.h"

void milestone4()
{
    hitButton();

    pickUpBucket();

    driveUpRamp();

    dropOffBucket();

    flipFertilizer();
    // Sleep(5.0);

    // flipFertilizer(false);
}

void waitUntilLight(int rev = 1)
{
    while (getHumidifierLight() == Light::NOLIGHT)
    {
    }
}

void ERCMain()
{
    // RCS.initialize("1240E4ZQS");
    // the servo needs to be configured in a main function,
    // so i just do it here
    servo.SetMin(500);
    servo.SetMax(2500);

    // waitUntilTouch();
    waitUntilLight();

    milestone4();
}