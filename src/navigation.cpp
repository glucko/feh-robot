#include <FEH.h>
#include "drive.h"
#include "constants.h"
#include "utils.h"
#include "navigation.h"

Drive drive = Drive(motorA, motorB, motorC);

void hitButton(int rev)
{
    drive.driveDirection(-1, Direction::AB);

    drive.driveDirection(2, Direction::AB);

    logger.log("finished hitButton()");
}

void pickUpBucket()
{

    drive.driveDirection(17, Direction::AB);

    drive.turn(-49);

    servo.SetDegree(96);
    Sleep(1.0);

    drive.driveDirection(4, Direction::AB, 20);

    servo.SetDegree(0);
    Sleep(1.0);

    logger.log("finished pickUpBucket()");
}

void dropOffBucket()
{
    drive.driveDirection(1, Direction::AB);

    servo.SetDegree(20);
    Sleep(.1);
    servo.SetDegree(30);
    Sleep(.1);
    servo.SetDegree(40);
    Sleep(.1);
    servo.SetDegree(50);
    Sleep(.1);
    servo.SetDegree(60);
    Sleep(.1);
    servo.SetDegree(70);

    Sleep(1.0);

    logger.log("finished dropOffBucket()");
}

void driveUpRamp(int rev)
{
    drive.turn(-15);
    drive.driveDirection(5, Direction::CA);
    drive.turn(15);

    drive.driveDirection(-21.5, Direction::AB);

    drive.turn(92);
    drive.driveDirection(rev * 33, Direction::AB, 35);

    logger.log("finished driveUpRamp()");
}

void flipFertilizer(bool flipUp)
{

    drive.driveDirection(-3, Direction::AB);

    drive.turn(-15);
    drive.driveDirection(10, Direction::CA);

    if (flipUp)
    {
        servo.SetDegree(SERVO_RAISED);
    }
    else
    {
        servo.SetDegree(SERVO_LOWERED);
    }
    Sleep(1.0);

    drive.turn(-30);
    drive.driveDirection(6, Direction::AB);

    switch (1)
    {
        // Left lever
    case 0:
        logger.log("Flipping left lever");

        drive.turn(-15);
        drive.driveDirection(4, Direction::CA);
        drive.turn(15);
        break;

        // Middle lever
    case 1:
        logger.log("Flipping middle lever");
        break;

        // Right lever
    case 2:
        logger.log("Flipping right lever");

        drive.turn(-15);
        drive.driveDirection(-2, Direction::CA);
        drive.turn(15);
        break;
    }

    if (flipUp)
    {
        servo.SetDegree(SERVO_LOWERED);
    }
    else
    {
        servo.SetDegree(SERVO_RAISED);
    }

    Sleep(1.0);

    logger.log("finished flipFertilizer()");
}
