#include <FEH.h>
#include "constants.h"
#include "utils.h"
#include "navigation.h"
#include "drive.h"

void aitUntilLight(int rev = 1)
{
    while (getHumidifierLight() == Light::NOLIGHT)
    {
    }
}

void ERCMain()
{
    // RCS.initialize("1240E4ZQS");
    servo.SetMin(500);
    servo.SetMax(2500);

    waitUntilTouch();

    driveToBucket();
    pickUpBucket();

    dropOffBucket();

    driveToRampFromBucket();
    driveUpRampAndRealign();

    driveToFertilizerFromTable();
    flipFertilizerDown();

    hitButton();

    goToWindowFromButton();
    pushWindow();

    driveToCompostFromWindow();
    spinCompost();
    hitButtonFromCompost();
}