#include "include/drive.h"
#include "include/constants.h"
#include "include/utils.h"
#include <FEHLCD.h>

Drive drive = Drive(motorA, motorB, motorC, .5);

void milestone2()
{
    drive.driveDirection(15, Direction::FORWARD, 25);

    // Drives up ramp
    drive.driveDirection(13, Direction::FORWARD, 25);

    // Corrects to center
    drive.driveDirection(1, Direction::RIGHT, 10);

    // Go above and read light
    drive.driveDirection(1, Direction::FORWARD, 10);

    // Face correct button
    switch (getHumidifierLight())
    {
    case 0:
        LCD.WriteLine("Light is red");
        drive.driveDirection(2, Direction::LEFT, NORMAL_POWER);
        break;
    case 1:
        LCD.WriteLine("Light is blue");
        drive.driveDirection(2, Direction::RIGHT, NORMAL_POWER);
        break;
    default:
        float val = cdsCell.Value();
        std::string msg = "Unable to read light. Value: " + std::to_string(val);
        LCD.WriteLine(msg.c_str());
        break;
    }

    // hit button
    drive.driveDirection(3, Direction::FORWARD, NORMAL_POWER);

    // Drive back down to start button
    drive.driveDirection(10, Direction::FORWARD, -NORMAL_POWER);
    drive.driveDirection(12, Direction::LEFT, NORMAL_POWER);
}

int main()
{

    waitUntilTouch();

    drive.turn(360, 25, true);

    LCD.WriteLine("All Done :)");
}