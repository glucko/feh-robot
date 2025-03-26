#include <FEH.h>
#include <Arduino.h>
#include "drive.h"
#include "constants.h"
#include "utils.h"

Drive drive = Drive(motorA, motorB, motorC);

void doFertilizer()
{
    switch (RCS.GetCorrectLever())
    {
        // Left lever
    case 0:
        drive.driveDirection(-2, Direction::BC);
        break;

        // Middle lever
    case 1:
        break;

        // Right lever
    case 2:
        drive.driveDirection(2, Direction::BC);
        break;
    }

    drive.driveDirection(2, Direction::AB);
}

void ERCMain()
{
    // Your code here!
    // RCS.InitializeTouchMenu("0300GXYZ");

    waitUntilTouch();

    FEHServo servo(FEHServo::Servo0);
    servo.TouchCalibrate();

    // getHumidifierLight();

    // drive.driveDirection(10, Direction::AB);
}