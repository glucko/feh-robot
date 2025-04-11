#include <FEH.h>
#include "constants.h"
#include "utils.h"
#include "navigation.h"
#include "drive.h"

void waitUntilLight(int rev = 1)
{
    float time = TimeNow();
    while (getHumidifierLight() == Light::NOLIGHT && TimeNow() - time < 30)
    {
    }
}

void ERCMain()
{
    RCS.InitializeTouchMenu("1240E4ZQS");
    servo.SetMin(500);
    servo.SetMax(2500);

    waitUntilTouch();
    waitUntilLight();
    hitStartButton();
    
    driveToBucket();
    pickUpBucket();
    driveToRampFromBucket();
    driveUpRampAndRealign();
    dropOffBucket();
    hitButton();

    goToWindowFromButton();
    pushWindow();

    driveToCompostFromWindow();
    spinCompost();
    hitButtonFromCompost();
}