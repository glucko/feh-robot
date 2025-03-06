#include <math.h>
#include "include/drive.h"
#include "include/utils.h"
#include "include/constants.h"
#include <FEHLCD.h>

Drive::Drive(Motor &m1, Motor &m2, Motor &m3, float correctionFactor)
    : motor1(m1), motor2(m2), motor3(m3), kP(correctionFactor) {}

void Drive::correctDriveStraight(Motor *mot1, Motor *mot2, int targetPower)
{
    int error = mot1->Counts() - mot2->Counts();

    int correction = clip(kP * error, -5, 5);

    LCD.WriteLine("Correction:");
    LCD.WriteLine(correction);

    mot1->SetPercent(targetPower - correction);
    // negative because this motor goes in opposite direction
    mot2->SetPercent(-(targetPower + correction));
}

void Drive::driveDirection(float distance, Direction direction, int power)
{
    resetAll();

    Motor *mot1;
    Motor *mot2;

    // Determines which motors will be turning based on direction
    switch (direction)
    {
    case Direction::FORWARD:
        mot1 = &motor1;
        mot2 = &motor2;
        break;

    case Direction::LEFT:
        mot1 = &motor2;
        mot2 = &motor3;
        break;

    case Direction::RIGHT:
        mot1 = &motor1;
        mot2 = &motor3;
        break;
    }

    // accounts for the fact that wheels are at an 120 deg angle
    int targetCounts = inchesToCounts(distance * cos(degToRad(60)));

    LCD.WriteLine("Target Counts: ");
    LCD.WriteLine(targetCounts);

    mot1->SetPercent(power);
    mot2->SetPercent(-power);

    // TODO: also add a time limit
    while ((mot1->Counts() + mot2->Counts()) / 2 <= targetCounts)
    {
        // logger.logToScreen(logger.getEncoderInfo());
        correctDriveStraight(mot1, mot2, power);
    }

    resetAll();
}

void Drive::turn(float degrees, int power, bool clockwise)
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
    while ((motor1.Counts() + motor2.Counts() + motor3.Counts()) / 3 <= targetCounts)
    {
    }

    resetAll();
}