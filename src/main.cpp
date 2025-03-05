#include "include/drive.h"
#include "include/sensor.h"
#include "include/constants.h"
int main()
{
    //Declaration of motors and sensors
    Drive drive = Drive(motorA, motorB, motorC);
    Sensor cdsSensor = Sensor();

    // Moves to ramp
    drive.driveDirection(15, Direction::FORWARD, 25);
    // Corrects to center
    drive.driveDirection(1, Direction::RIGHT, 10);
    // Drives up ramp
    drive.driveDirection(13, Direction::FORWARD, 25);
    // Turns to sensor
    drive.driveDirection(, Direction::TURN, 15);
    // cdsSensor.cdsIsBlue(cdsCell, motorA, motorB, motorC);
    // drive.driveDirection(15, Direction::FORWARD, 15);
}