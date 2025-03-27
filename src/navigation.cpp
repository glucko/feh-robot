#include <FEH.h>
#include "drive.h"
#include "constants.h"
#include "utils.h"

Drive drive = Drive(motorA, motorB, motorC);

void hitButton(int rev = 1)
{
    drive.driveDirection(-2, Direction::AB);

    drive.driveDirection(1, Direction::AB);
}

void pickUpBucket()
{
    servo.SetDegree(SERVO_LOWERED);

    drive.turn(-45);
    drive.driveDirection(12, Direction::AB);

    servo.SetDegree(SERVO_RAISED);

    drive.driveDirection(-15, Direction::AB);

    drive.turn(45);
}

void dropOffBucket()
{
    drive.driveDirection(12, Direction::AB);
    servo.SetDegree(SERVO_LOWERED);
}

void driveUpRamp(int rev)
{
    drive.turn(45);
    drive.driveDirection(rev * 33, Direction::AB);
}

void flipFertilizer(bool flipUp)
{
    if (flipUp)
    {
        servo.SetDegree(SERVO_LOWERED);
    }
    else
    {
        servo.SetDegree(SERVO_RAISED);
    }

    switch (RCS.GetCorrectLever())
    {
        // Left lever
    case 0:
        drive.driveDirection(-2, Direction::BC);
        break;

        // Middle lever
    case 1:
        break;

        // Right lever
    case 2:
        drive.driveDirection(2, Direction::BC);
        break;
    }

    if (flipUp)
    {
        servo.SetDegree(SERVO_RAISED);
    }
    else
    {
        servo.SetDegree(SERVO_LOWERED);
    }

    drive.driveDirection(2, Direction::AB);
}
