#include <FEHBattery.h>
#include <FEHLCD.h>
#include "include/constants.h"
#include "include/utils.h"
// #include "include/drive_straight.h"

int main()
{
    LCD.WriteLine("Hello world!");

    LCD.WriteLine(Battery.Voltage());

    logger.logToScreen("hello world");
    logger.logToSD("hello world");

    // // TODO: refactor to use directions instead of motors
    // DriveStraight driveStraightAB = DriveStraight(motorA, motorB, encoderA, encoderB);

    // // drive straight for 10 inches in the direction of motors A and B
    // driveStraightAB.driveStraight(10);

    // close logger
    // logger.closeLogger();
}