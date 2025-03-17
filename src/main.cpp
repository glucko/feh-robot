#include "include/drive.h"
#include "include/constants.h"
#include "include/utils.h"
#include <FEHLCD.h>
#include <FEHBattery.h>

Drive drive = Drive(motorA, motorB, motorC, .5);
Logger logger = Logger();

int main()
{
    logger.log(logger.getEncoderInfo());
}