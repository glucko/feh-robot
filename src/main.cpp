#include "include/utils.h"
#include "include/constants.h"
#include "include/drive.h"
#include <FEHUtility.h>

Drive drive = Drive(motorA, motorB, motorC);
float sleepTime = .5;

void alignBottomWindow(int rev = 1)
{
    logger.log("Aligning bottom window");

    // Go to corner
    drive.driveDirection(rev * 30, Direction::AB);
    Sleep(sleepTime);

    // Align with corner
    drive.driveDirection(rev * 5, Direction::BC);

    logger.log("Aligned bottom window");
}

// Assumes starting at beginning
void driveUpRamp(int rev = 1)
{
    logger.log("Driving up ramp");

    // Align with ramp
    drive.turn(45);
    Sleep(sleepTime);

    // Drive up ramp
    drive.driveDirection(rev * 33, Direction::AB);
    Sleep(sleepTime);

    logger.log("Drove up ramp");
}

void hitButton(int rev = 1)
{
    // Hit button
    drive.driveDirection(-2, Direction::AB);
    Sleep(sleepTime);

    drive.driveDirection(1, Direction::AB);
    Sleep(sleepTime);

    logger.log("Hit button");
}

void goForwardHighPowerB()
{
    resetAll();
    // accounts for the fact that wheels are at an 120 deg angle
    int targetCounts = inchesToCounts(10) * (30.0 / 35.0);

    motorA.SetPercent(45);
    motorB.SetPercent(-35);

    motorC.SetPercent(15);

    // TODO: also add a time limit
    while ((motorA.Counts() + motorB.Counts()) / 2 <= targetCounts)
    {
    }

    resetAll();
}

void goForwardHighPowerA()
{
    resetAll();
    // accounts for the fact that wheels are at an 120 deg angle
    int targetCounts = inchesToCounts(10) * (30.0 / 35.0);

    motorA.SetPercent(15);
    motorB.SetPercent(35);

    motorC.SetPercent(-35);

    // TODO: also add a time limit
    while ((motorA.Counts() + motorB.Counts()) / 2 <= targetCounts)
    {
    }

    resetAll();
}

void doWindow(int rev = 1)
{
    logger.log("Doing window");

    drive.turn(-45);
    Sleep(sleepTime);

    drive.driveDirection(rev * 4, Direction::AB);
    Sleep(sleepTime);

    drive.turn(-75);
    Sleep(sleepTime);

    drive.driveDirection(rev * 10, Direction::AB, 35);
    Sleep(sleepTime);

    goForwardHighPowerB();
    Sleep(sleepTime);

    logger.log("Did window");
}

void waitUntilLight(int rev = 1)
{
    while (getHumidifierLight() == -1)
    {
    }
}

void reverseHandle()
{
    drive.turn(-360);
    Sleep(sleepTime);

    drive.driveDirection(4, Direction::CA);
    Sleep(sleepTime);

    goForwardHighPowerA();
}

int main()
{
    // waitUntilTouch();
    waitUntilLight();
    hitButton();
    driveUpRamp();
    doWindow();

    reverseHandle();
}