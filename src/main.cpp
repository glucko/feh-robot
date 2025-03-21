#include "include/utils.h"
#include "include/constants.h"
#include "include/drive.h"

Drive drive = Drive(motorA, motorB, motorC);

void alignBottomWindow(int rev = 1)
{
    logger.log("Aliging bottom window");

    // Go to corner
    drive.driveDirection(rev * 30, Direction::AB);

    // Align with corner
    drive.driveDirection(rev * 5, Direction::BC);

    logger.log("Aligned bottom window");
}

// Assumes starting at beginning
void driveUpRamp(int rev = 1)
{
    logger.log("Driving up ramp");

    // Align with ramp
    drive.turn(60);

    // Drive up ramp
    drive.driveDirection(rev * 30, Direction::AB);

    logger.log("Drove up ramp");
}

void hitButton(int rev = 1)
{
    // Hit button
    drive.driveDirection(-1, Direction::AB);
    drive.driveDirection(1, Direction::AB);

    logger.log("Hit button");
}

void doWindow(int rev = 1)
{
    logger.log("Doing window");

    drive.turn(60);
    drive.driveDirection(rev * 30, Direction::BC);

    logger.log("Did window");
}

void waitUntilLight(int rev = 1)
{
    while (getHumidifierLight() == -1)
    {
    }
}

int main()
{
    waitUntilLight();
    hitButton();
    driveUpRamp();
    doWindow();

    // Do everything in reverse
    waitUntilLight(-1);
    hitButton(-1);
    driveUpRamp(-1);
    doWindow(-1);
}