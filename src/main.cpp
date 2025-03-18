#include "include/utils.h"
#include "include/constants.h"
#include "include/drive.h"

Drive drive = Drive(motorA, motorB, motorC);

int main()
{
    waitUntilTouch();

    drive.driveDirection(8, Direction::AB);
}