#include "constants.h"
#include "drive_straight.h"

int main()
{
    // TODO: refactor to use directions instead of motors
    DriveStraight driveStraight = DriveStraight(motorA, motorB, encoderA, encoderB);

    // drive straight for 10 inches in the direction of motors A and B
    driveStraight.driveStraight(10);
}