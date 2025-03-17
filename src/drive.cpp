#include <math.h>
#include <FEHLCD.h>
#include "include/drive.h"
#include "include/utils.h"
#include "include/constants.h"
#include "include/MiniPID.h"

Drive::Drive(Motor &m1, Motor &m2, Motor &m3, float correctionFactor)
    : motor1(m1), motor2(m2), motor3(m3), kP(correctionFactor), pid(1, 1, 1)
{
}

void Drive::correctDriveStraight(Motor *mot1, Motor *mot2, int targetPower)
{
    // Use PID to calculate the correction based on the encoder difference
    float correction = pid.getOutput(mot1->Counts() - mot2->Counts(), 0.0);

    // Adjust the motor power with correction, ensuring it stays within 5 of targetPower
    int maxVal = targetPower + 5;
    int adjustedPower1 = clamp(targetPower + static_cast<int>(correction * targetPower), -maxVal, maxVal);
    int adjustedPower2 = clamp(targetPower - static_cast<int>(correction * targetPower), -maxVal, maxVal);

    mot1->SetPercent(adjustedPower1);
    mot2->SetPercent(adjustedPower2);
}

void Drive::driveDirection(float distance, Direction direction, int power)
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

    // accounts for the fact that wheels are at an 120 deg angle
    int targetCounts = inchesToCounts(distance * .8);

    mot1->SetPercent(power);
    mot2->SetPercent(-power);

    // TODO: also add a time limit
    while ((mot1->Counts() + mot2->Counts()) / 2 <= targetCounts)
    {
        LCD.WriteLine(cdsCell.Value());
        correctDriveStraight(mot1, mot2, power);
    }

    resetAll();
}

void Drive::turn(float degrees, bool clockwise, int power)
{
    resetAll();

    // If counterclockwise, invert the power
    if (!clockwise)
    {
        power = -power;
    }

    float angleInRadians = degToRad(degrees);
    float arcLength = (ROBOT_DIAMETER / 2) * angleInRadians;

    // Convert arc length to encoder counts
    int targetCounts = inchesToCounts(arcLength);

    // Set all motors to the same power to rotate the robot
    motor1.SetPercent(power);
    motor2.SetPercent(power);
    motor3.SetPercent(power);

    // Wait until the rotation is complete
    while ((motor1.Counts() + motor2.Counts() + motor3.Counts()) / 3 < targetCounts)
    {
    }

    resetAll();
}

void Drive::driveUntilLight(Direction direction, int power)
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

    mot1->SetPercent(power);
    mot2->SetPercent(-power);

    // TODO: also add a time limit
    while (getHumidifierLight() == -1)
    {
        correctDriveStraight(mot1, mot2, power);
    }

    resetAll();
}