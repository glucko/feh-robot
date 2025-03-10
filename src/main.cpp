#include "include/drive.h"
#include "include/constants.h"
#include "include/utils.h"
#include <FEHLCD.h>
#include <FEHBattery.h>

Drive drive = Drive(motorA, motorB, motorC, .5);

void milestone2()
{
    // Hit start button
    drive.driveDirection(1.2, Direction::AB, -NORMAL_POWER);
    Sleep(1.0);

    drive.driveDirection(3, Direction::AB);
    Sleep(1.0);

    drive.driveDirection(6, Direction::BC);
    Sleep(1.0);

    drive.turn(40, true);
    Sleep(1.0);

    // Drives up ramp
    drive.driveDirection(41, Direction::AB);
    Sleep(1.0);

    // Go to humidifier light
    drive.turn(28, true);
    Sleep(1.0);

    // Drive until humidifier button
    drive.driveUntilLight(Direction::CA, -NORMAL_POWER);
    Sleep(1.0);

    switch (getHumidifierLight())
    {
    case 0:
        LCD.WriteLine("Light is red");
        drive.driveDirection(1, Direction::AB);
        break;
    case 1:
        LCD.WriteLine("Light is blue");
        drive.driveDirection(1, Direction::CA);
        break;
    default:
        float val = cdsCell.Value();
        LCD.WriteLine("Unable to read light. Value: ");
        LCD.WriteLine(val);
        break;
    }
    Sleep(1.0);

    // hit button
    drive.driveDirection(11, Direction::CA, -NORMAL_POWER);
    Sleep(1.0);

    // Drive back down to start button
    drive.driveDirection(25, Direction::CA);
    Sleep(1.0);

    drive.turn(30, true);
    Sleep(1.0);

    drive.driveDirection(45, Direction::BC);
    Sleep(1.0);
}

void waitUntilLight()
{
    while (cdsCell.Value() > noLightThreshold)
    {
    }
}

int main()
{

    waitUntilLight();

    milestone2();

    LCD.WriteLine(Battery.Voltage());

    LCD.WriteLine("All Done :)");
}