#include <FEH.h>
#include <PID_v1.h>
#include "drive.h"
#include "utils.h"
#include "constants.h"

const float SLEEPTIME = .5;

Drive::Drive(Motor &m1, Motor &m2, Motor &m3)
    : motor1(m1), motor2(m2), motor3(m3)
{
}

void Drive::driveWithMode(DriveMode mode, Direction direction, int power, float distance, float timeOut)
{
    resetAll();

    Motor *mot1;
    Motor *mot2;

    // Determines which motors will be turning based on direction
    switch (direction)
    {
    case Direction::AB:
        mot1 = &motor1;
        mot2 = &motor2;
        break;

    case Direction::BC:
        mot1 = &motor2;
        mot2 = &motor3;
        break;

    case Direction::CA:
        mot1 = &motor1;
        mot2 = &motor3;
        break;
    }

    int targetCounts = 0;

    // Handle distance mode specifics
    if (mode == DriveMode::DISTANCE)
    {
        // Reverses power if distance is negative
        if (distance < 0)
        {
            power = -power;
            distance = -distance;
        }

        // accounts for the fact that wheels are at a 120 deg angle
        targetCounts = inchesToCounts(distance) * (30.0 / 35.0);
    }

    double input = mot1->Counts() - mot2->Counts();
    double target = 0;
    double adjustedPower = power;

    PID pid(&input, &adjustedPower, &target, 0.1, 0.001, 0.01, DIRECT);
    pid.SetMode(AUTOMATIC);

    float startTime = TimeNow();
    bool shouldContinue = true;
    while (shouldContinue)
    {
        input = mot1->Counts() - mot2->Counts();
        pid.Compute();
        adjustedPower = constrain(adjustedPower, power - 5, power + 5);

        mot1->SetPercent(adjustedPower);
        mot2->SetPercent(-adjustedPower);

        // Determine if we should continue based on the mode
        if (TimeNow() - startTime > timeOut)
        {
            shouldContinue = false;
        }
        else if (mode == DriveMode::DISTANCE)
        {
            shouldContinue = (mot1->Counts() + mot2->Counts()) / 2 <= targetCounts;
        }
        else if (mode == DriveMode::LIGHT)
        {
            shouldContinue = getHumidifierLight() == Light::NOLIGHT;
        }
    }

    resetAll();
    Sleep(SLEEPTIME);
}

// Wrapper functions to maintain original API
void Drive::driveDirection(float distance, Direction direction, int power, float startTime)
{
    driveWithMode(DriveMode::DISTANCE, direction, power, distance, startTime);
}

void Drive::driveUntilLight(Direction direction, int power, float startTime)
{
    driveWithMode(DriveMode::LIGHT, direction, power, 0, startTime);
}

void Drive::turn(float degrees, int power)
{
    resetAll();

    Motor *mot1 = &motor1;
    Motor *mot2 = &motor2;
    Motor *mot3 = &motor3;

    // If counterclockwise, invert the power
    if (degrees < 0)
    {
        power = -power;
        degrees = -degrees;
    }

    float arcLength = (ROBOT_DIAMETER / 2) * degToRad(degrees);

    double input = (mot1->Counts() + mot2->Counts() + mot3->Counts()) / 3;
    double target = inchesToCounts(arcLength);
    double adjustedPower = power;

    PID pid(&input, &adjustedPower, &target, 0, 0, 0, DIRECT);
    pid.SetMode(AUTOMATIC);

    while ((motor1.Counts() + motor2.Counts() + motor3.Counts()) / 3 < target)
    {
        input = (mot1->Counts() + mot2->Counts() + mot3->Counts()) / 3;
        pid.Compute();
        adjustedPower = constrain(adjustedPower, power - 5, power + 5);

        mot1->SetPercent(adjustedPower);
        mot2->SetPercent(adjustedPower);
        mot3->SetPercent(adjustedPower);
    }

    resetAll();

    Sleep(SLEEPTIME);
}