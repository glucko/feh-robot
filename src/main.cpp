#include "include/utils.h"
#include "include/constants.h"
#include "include/drive.h"

Drive drive = Drive(motorA, motorB, motorC);

void alignBottomWindow()
{
    // Go to corner
    drive.driveDirection(30, Direction::AB);

    // Align with corner
    drive.driveDirection(5, Direction::BC);
}

// Starting at beginning
void driveUpRamp()
{
    // Go to corner
    drive.driveDirection(30, Direction::AB);

    // Align with corner
    drive.driveDirection(5, Direction::BC);
}

void hitButton()
{
    // Hit button
    drive.driveDirection(-1, Direction::AB);
    drive.driveDirection(1, Direction::AB);
}

int main()
{
    waitUntilTouch();

    drive.driveDirection(8, Direction::AB);
}