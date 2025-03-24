#include <FEH.h>
#include <Arduino.h>
#include "drive.h"
#include "constants.h"
#include "utils.h"

Drive drive = Drive(motorA, motorB, motorC);
void ERCMain()
{
    // Your code here!
    // RCS.InitializeTouchMenu("0300GXYZ");

    waitUntilTouch();

    drive.driveDirection(5, Direction::AB);
}