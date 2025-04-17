#include <FEH.h>
#include "drive.h"
#include "constants.h"
#include "utils.h"
#include "navigation.h"

Drive drive = Drive(motorA, motorB, motorC);

void hitStartButton()
{
    drive.driveDirection(-1.3, Direction::AB);
    drive.driveDirection(2, Direction::AB);

    logger.log("Hit button");
}

void driveToBucket()
{
    drive.driveDirection(18, Direction::AB);
    drive.turn(-45);

    logger.log("Drove to button");
}

void pickUpBucket()
{

    servoLeveling(96);
    drive.driveDirection(4.3, Direction::AB, 15);
    servoLeveling(0);

    logger.log("Picked up Bucket");
}

void dropOffBucket()
{

    drive.driveDirection(1, Direction::AB);

    servoLeveling(90);

    Sleep(1.0);

    logger.log("finished dropOffBucket()");
    
    Sleep(.5);

    drive.driveDirection(1, Direction::AB);
    servoLeveling(0);
}

void driveToRampFromBucket()
{
    drive.turn(-15);
    drive.driveDirection(5, Direction::CA);
    drive.turn(15);

    drive.driveDirection(-21, Direction::AB);
}

void driveUpRampAndRealign()
{
    drive.turn(91);
    drive.driveDirection(35, Direction::AB, 35);

    logger.log("finished driveUpRamp()");
}

void driveToFertilizerFromTable()
{
    drive.driveDirection(-3, Direction::AB);

    drive.turn(-15);
    drive.driveDirection(10, Direction::CA);

    logger.log("drove to fertilizer");
}

void flipFertilizerDown()
{
    servoLeveling(0);
    drive.turn(-32);
    drive.driveDirection(7, Direction::AB);

    servoLeveling(SERVO_LOWERED + 5);
    servoLeveling(0);

    logger.log("finished flipFertilizer()");
}

void hitButton()
{
    drive.driveDirection(-1, Direction::AB);
    drive.turn(-31.5);
    /*drive.driveUntilLight(Direction::AB);

    if (getHumidifierLight() == Light::BLUELIGHT)
        drive.driveDirection(3, Direction::BC);
    else
        drive.driveDirection(-3, Direction::BC);*/

    drive.driveDirection(24, Direction::CA);
}

void goToWindowFromButton()
{
    drive.driveDirection(-10, Direction::AB);
    drive.driveDirection(5, Direction::BC);
}

void pushWindow()
{
    resetAll();

    int targetCounts = inchesToCounts(10) * (30.0 / 35.0);
    motorA.SetPercent(45);
    motorB.SetPercent(-35);
    motorC.SetPercent(15);

    while (!RCS.isWindowOpen() && (motorA.Counts() + motorB.Counts()) / 2 <= targetCounts)
    {
    }

    resetAll();
}

void driveToCompostFromWindow()
{
    // drive.driveDirection(5, Direction::CA);
    // drive.driveDirection(-15, Direction::AB);
    // drive.driveDirection(1.5, Direction::AB);
    // drive.turn(90);
    // drive.driveDirection(-18, Direction::AB);
    // drive.turn(-90);
    // drive.driveDirection(10, Direction::AB);

    drive.driveDirection(-24, Direction::CA);
    drive.turn(31.5);
    drive.driveDirection(-30, Direction::AB);
    drive.turn(-135);
    drive.driveDirection(15, Direction::AB);
}

void driveToCompostFromStart()
{
    // Making pseudocode for Benjamin

    // Set servo to vertical position
    servo.SetDegree(0);
    // Drive forward a bit from the button
    drive.driveDirection(9, Direction::AB);
    // Turn left to drive towards composter
    drive.turn(16);

    // Drive forward til in range of composter
    drive.driveDirection(9, Direction::CA);
    // Turn to make arm face composter
    drive.turn(-157);
    drive.driveDirection(-0.5, Direction::AB);

    int numFlips = 0;
    // Repeat until fully spinned one way
    while (numFlips < 4)
    {
        servoLeveling(0);
        drive.driveDirection(3.5, Direction::AB);
        servoLeveling(150);
        drive.driveDirection(-3.5, Direction::AB);
        numFlips++;
    }
    numFlips = 0;

    // Rotating back to original position (BONUS)
    // Now do the same thing but set servo to lowest possible position, then rotate up instead of down
    while (numFlips < 4)
    {
        servoLeveling(160);
        drive.driveDirection(4.2, Direction::AB);
        servoLeveling(0);
        drive.driveDirection(-4, Direction::AB);
        numFlips++;
    }
}

void spinCompost()
{
    int numFlips = 0;
    // Repeat until fully spinned one way
    while (numFlips < 4)
    {
        servoLeveling(0);
        drive.driveDirection(3.5, Direction::AB);
        servoLeveling(150);
        drive.driveDirection(-3.5, Direction::AB);
        numFlips++;
    }
    numFlips = 0;
}

void hitButtonFromCompost()
{
    drive.turn(157);
    drive.driveDirection(-10, Direction::CA);
    drive.turn(-16);
    drive.driveDirection(-12, Direction::AB);
}