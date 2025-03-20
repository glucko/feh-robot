#include <FEHUtility.h>
#include "include/utils.h"
#include "include/constants.h"
#include "include/drive.h"

Drive drive = Drive(motorA, motorB, motorC);
void milestone2()
{
    // Hit start button
    drive.driveDirection(-1.2, Direction::AB);
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
        logger.log("Light is red");
        drive.driveDirection(1, Direction::AB);
        break;
    case 1:
        logger.log("Light is blue");
        drive.driveDirection(1, Direction::CA);
        break;
    default:
        float val = cdsCell.Value();
        logger.log("Unable to read light. Value: ");
        logger.log(std::to_string(val));
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
    waitUntilTouch();
    // drive.turn(360);

    drive.driveDirection(30, Direction::AB, 25);

    // waitUntilLight();
    // milestone2();
}