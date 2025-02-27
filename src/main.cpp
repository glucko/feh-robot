#include "../include/constants.h"
#include "../include/drive_straight.h"
#include "../include/utils.h"

int main()
{
    // TODO: refactor to use directions instead of motors
    DriveStraight driveStraightAB = DriveStraight(motorA, motorB, encoderA, encoderB);

    // drive straight for 10 inches in the direction of motors A and B
    driveStraightAB.driveStraight(10);

    // close logger
    logger.closeLogger();
}