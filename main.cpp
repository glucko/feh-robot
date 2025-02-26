#include <FEHMotor.h>
#include "constants.h"
#include "drive_straight.h"

int main()
{
    DriveStraight driveStraight = DriveStraight(motorA, motorB, encoderA, encoderB);

    // drive straight for 10 inches with motors A and B
    driveStraight.driveStraight(10);
}