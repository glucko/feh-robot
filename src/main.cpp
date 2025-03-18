#include "include/logger.h"
#include "include/utils.h"
#include "include/constants.h"

Logger logger = Logger(1.0);

int main()
{
    waitUntilTouch();

    // motorA.SetPercent(10);
    // motorB.SetPercent(10);
    // motorC.SetPercent(10);

    while (true)
    {
        logger.log(logger.getEncoderInfo());
    }
}