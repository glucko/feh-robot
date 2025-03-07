#include "include/drive.h"
#include "include/constants.h"
#include "include/utils.h"
#include <FEHLCD.h>
#include <FEHBattery.h>

Drive drive = Drive(motorA, motorB, motorC, .5);

void milestone2()
{
    // Hit start button
    drive.driveDirection(3, Direction::AB, -NORMAL_POWER);
    Sleep(1.0);

    drive.driveDirection(3, Direction::AB);
    Sleep(1.0);

    drive.driveDirection(6, Direction::BC);
    Sleep(1.0);

    drive.turn(30, true);
    Sleep(1.0);

    // Drives up ramp
    drive.driveDirection(27, Direction::CA);
    Sleep(1.0);

    // Go to humidifier light
    drive.turn(30, true);
    Sleep(1.0);

    drive.driveDirection(16, Direction::BC);
    Sleep(1.0);

    // Face correct button (no cds cell so just putting in left button for now)
    drive.driveDirection(2, Direction::BC);
    Sleep(1.0);
    // switch (getHumidifierLight())
    // {
    // case 0:
    //     LCD.WriteLine("Light is red");
    //     drive.driveDirection(2, Direction::LEFT);
    //     break;
    // case 1.0:
    //     LCD.WriteLine("Light is blue");
    //     drive.driveDirection(2, Direction::RIGHT);
    //     break;
    // default:
    //     float val = cdsCell.Value();
    //     std::string msg = "Unable to read light. Value: " + std::to_string(val);
    //     LCD.WriteLine(msg.c_str());
    //     break;
    // }

    // hit button
    drive.driveDirection(8, Direction::BC);
    Sleep(1.0);

    // Drive back down to start button
    drive.driveDirection(24, Direction::BC, -NORMAL_POWER);
    Sleep(1.0);

    drive.turn(30, true);
    Sleep(1.0);

    drive.driveDirection(27, Direction::AB, -NORMAL_POWER);
    Sleep(1.0);
}

int main()
{

    waitUntilTouch();

    milestone2();

    LCD.WriteLine(Battery.Voltage());

    LCD.WriteLine("All Done :)");
}