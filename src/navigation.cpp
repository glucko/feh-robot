#include <FEH.h>
#include "drive.h"
#include "constants.h"
#include "utils.h"

Drive drive = Drive(motorA, motorB, motorC);

void hitButton(int rev = 1)
{
    drive.driveDirection(-2, Direction::AB);

    drive.driveDirection(1, Direction::AB);

    logger.log("finished hitButton()");
}

void pickUpBucket()
{
    servo.SetDegree(SERVO_LOWERED);

    drive.turn(-45);
    drive.driveDirection(12, Direction::AB);

    servo.SetDegree(SERVO_RAISED);

    drive.driveDirection(-15, Direction::AB);

    drive.turn(45);

    logger.log("finished pickUpBucket()");
}

void dropOffBucket()
{
    drive.driveDirection(12, Direction::AB);
    servo.SetDegree(SERVO_LOWERED);

    logger.log("finished dropOffBucket()");
}

void driveUpRamp(int rev)
{
    drive.turn(45);
    drive.driveDirection(rev * 33, Direction::AB);

    logger.log("finished driveUpRamp()");
}

void flipFertilizer(bool flipUp)
{
    if (flipUp)
        servo.SetDegree(SERVO_LOWERED);
    else
        servo.SetDegree(SERVO_RAISED);

    switch (RCS.GetCorrectLever())
    {
        // Left lever
    case 0:
        logger.log("Flipping left lever");
        drive.driveDirection(-2, Direction::BC);
        break;

        // Middle lever
    case 1:
        logger.log("Flipping middle lever");
        break;

        // Right lever
    case 2:
        logger.log("Flipping right lever");
        drive.driveDirection(2, Direction::BC);
        break;
    }

    if (flipUp)
        servo.SetDegree(SERVO_RAISED);
    else
        servo.SetDegree(SERVO_LOWERED);

    drive.driveDirection(2, Direction::AB);

    logger.log("finished flipFertilizer()");
}
