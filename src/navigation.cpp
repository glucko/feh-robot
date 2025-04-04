#include <FEH.h>
#include "drive.h"
#include "constants.h"
#include "utils.h"
#include "navigation.h"

Drive drive = Drive(motorA, motorB, motorC);

void hitButton(int rev)
{
    drive.driveDirection(-1.3, Direction::AB);

    drive.driveDirection(2, Direction::AB);

    logger.log("finished hitButton()");
}

void pickUpBucket()
{

    drive.driveDirection(17.5, Direction::AB);

    drive.turn(-45);

    servoLeveling(0, 96);
    Sleep(1.0);

    drive.driveDirection(4.3, Direction::AB, 15);

    servoLeveling(96, 0);

    Sleep(.5);

    logger.log("finished pickUpBucket()");
}

void dropOffBucket()
{
    drive.driveDirection(1, Direction::AB);

    servoLeveling(0, 90);

    Sleep(1.0);

    logger.log("finished dropOffBucket()");

    servoLeveling(90, 0);
    Sleep(.5);

    drive.driveDirection(1, Direction::AB);
}

void driveUpRamp(int rev)
{
    drive.turn(-15);
    drive.driveDirection(5, Direction::CA);
    drive.turn(15);

    drive.driveDirection(-21, Direction::AB);

    drive.turn(93);
    drive.driveDirection(rev * 33, Direction::AB, 35);

    logger.log("finished driveUpRamp()");
}

void flipFertilizer()
{

    drive.driveDirection(-3, Direction::AB);

    drive.turn(-15);
    drive.driveDirection(10, Direction::CA);

    servo.SetDegree(SERVO_RAISED);
    Sleep(1.0);

    drive.turn(-32);
    drive.driveDirection(7, Direction::AB);

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

    servo.SetDegree(SERVO_LOWERED + 5);

    Sleep(1.0);

    servo.SetDegree(0);

    logger.log("finished flipFertilizer()");
}

void spinCompost() 
{
    servoLeveling(0, 75);
    
    drive.turn(15);
    drive.driveDirection(5, Direction::CA);
    
    drive.turn(-1440, 10);

}