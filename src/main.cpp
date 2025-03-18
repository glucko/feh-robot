#include "include/utils.h"
#include "include/constants.h"
#include "include/drive.h"
#include <FEHUtility.h>

Drive drive = Drive(motorA, motorB, motorC);

int main()
{
    waitUntilTouch();

    motorA.SetPercent(25);
    motorB.SetPercent(25);
    motorC.SetPercent(25);

    while (true)
    {
        logger.log("Time: " + std::to_string(TimeNow()) + "\n\n" + logger.getEncoderInfo());
    }
}