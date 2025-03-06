#include "include/drive.h"
#include "include/constants.h"
#include "include/utils.h"
#include <FEHLCD.h>

int main()
{
    Drive drive = Drive(motorA, motorB, motorC);

    // Drive up ramp
    drive.driveDirection(12, Direction::FORWARD, NORMAL_POWER);

    // Face buttons
    drive.turn(90, NORMAL_POWER, true);

    // Drive to buttons
    drive.driveDirection(12, Direction::FORWARD, NORMAL_POWER);

    int lightColor = getHumidifierLight();

    switch (lightColor)
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

    LCD.WriteLine("All Done :)");
}