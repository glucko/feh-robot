#include <math.h>
#include <FEHLCD.h>
#include "include/drive.h"
#include "include/utils.h"
#include "include/constants.h"
#include "include/MiniPID.h"

Drive::Drive(Motor &m1, Motor &m2, Motor &m3)
    : motor1(m1), motor2(m2), motor3(m3), pid(.002, 0, 0), pid2(.1, 0, 0)
{
}

void Drive::correctDriveStraight(Motor *mot1, Motor *mot2, int targetPower)
{
    int error = mot1->Counts() - mot2->Counts();

    // Apply a deadband: if error is too small, skip correction
    if (abs(error) < 3)
    {
        return;
    }

    float correction = pid.getOutput(error, 0.0);
    float scalingFactor = 0.077;
    int scaledCorrection = static_cast<int>(correction * scalingFactor);

    // Apply the correction to the motor power
    int motor1Power = targetPower + scaledCorrection;
    int motor2Power = targetPower - scaledCorrection;

    // logger.logWithDelay("motor1Power: " + std::to_string(motor1Power) + "\n" + "motor2Power: " + std::to_string(motor2Power));

    mot1->SetPercent(motor1Power);
    mot2->SetPercent(-motor2Power);
}

void Drive::correctDriveDistance(Motor *mot1, Motor *mot2, int targetCounts)
{
    int counts = (mot1->Counts() + mot2->Counts()) / 2;
    int error = 0;

    float slowdownThreshold = 1 / 5 * targetCounts;

    float correction = pid2.getOutput(counts, targetCounts);

    // Apply the correction to the motor power
    int motor1Power = correction;
    int motor2Power = correction;

    // // Deceleration: Reduce power as it gets closer
    // float distanceRemaining = abs(targetCounts - counts);
    // if (distanceRemaining < slowdownThreshold)
    // {
    //     motor1Power *= (int)distanceRemaining / slowdownThreshold;
    //     motor2Power *= (int)distanceRemaining / slowdownThreshold;
    // }

    // logger.logWithDelay("motor1Power: " + std::to_string(motor1Power) + "\n" + "motor2Power: " + std::to_string(motor2Power));

    mot1->SetPercent(motor1Power);
    mot2->SetPercent(-motor2Power);
}

void Drive::driveDirection(float distance, Direction direction, int power)
{
    resetAll();
    pid.reset();
    pid2.setOutputLimits(5, 10);

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

    if (distance < 0)
    {
        power = -power;
        distance = -distance;
    }

    // accounts for the fact that wheels are at an 120 deg angle
    int targetCounts = inchesToCounts(distance) * (30.0 / 35.0);

    mot1->SetPercent(power);
    mot2->SetPercent(-power);

    // TODO: also add a time limit
    while ((mot1->Counts() + mot2->Counts()) / 2 <= targetCounts)
    {
        correctDriveStraight(mot1, mot2, power);
        // correctDriveDistance(mot1, mot2, targetCounts);
    }

    resetAll();
}

void Drive::turn(float degrees, bool clockwise, int power)
{
    resetAll();

    // If counterclockwise, invert the power
    if (!clockwise || degrees < 0)
    {
        power = -power;
        degrees = -degrees;
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
    while ((motor1.Counts() + motor2.Counts()) / 2 < targetCounts)
    {
        // logger.log(logger.getEncoderInfo());
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