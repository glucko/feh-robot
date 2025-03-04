#include "include/drive.h"
#include "include/constants.h"
int main()
{
    Drive drive = Drive(motorA, motorB, motorC);

    drive.driveDirection(6, Direction::FORWARD, 25);
}