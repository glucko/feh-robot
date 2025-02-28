// #include "include/constants.h"
// #include "include/drive_straight.h"
// #include "include/utils.h"
#include <FEHLCD.h>
#include <FEHMotor.h>

FEHMotor motorA(FEHMotor::Motor0, 9);
FEHMotor motorB(FEHMotor::Motor1, 9);
FEHMotor motorC(FEHMotor::Motor2, 9);

void waitUntilTouch()
{
    float left;
    float right;

    while (!LCD.Touch(&left, &right))
    {
    }

    while (LCD.Touch(&left, &right))
    {
    }
}

int main()
{
    LCD.WriteLine("hello world!");
    waitUntilTouch();

    // Run motors forward until it is up ramp
    motorA.SetPercent(20);
    motorB.SetPercent(20);
    float curTime = TimeNow();

    while (TimeNow() - curTime < 5)
    {
    }

    // Go back down ramp
    motorA.SetPercent(-20);
    motorB.SetPercent(-20);

    curTime = TimeNow();
    while (TimeNow() - curTime < 5)
    {
    }

    // Stop motors
    motorA.SetPercent(0);
    motorB.SetPercent(0);
}