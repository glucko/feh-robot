#include <FEHLCD.h>
#include <FEHBattery.h>
#include "include/drive.h"
#include "include/constants.h"
#include "include/utils.h"
#include "include/logger.h"

Drive drive = Drive(motorA, motorB, motorC, .5);
Logger logger = Logger();

int main()
{
    logger.log(logger.getEncoderInfo());
}