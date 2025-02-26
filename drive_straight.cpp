#include <math.h>

#include "drive_straight.h"
#include "utils.h"
#include "constants.h"

// Constructor
DriveStraight::DriveStraight(FEHMotor &m1, FEHMotor &m2, DigitalEncoder &e1, DigitalEncoder &e2, float correctionFactor, int s1)
    : motor1(m1), motor2(m2), encoder1(e1), encoder2(e2), kP(correctionFactor), speed(s1) {}

// Compute encoder error between two wheels
int DriveStraight::computeError()
{
    return encoder1.Counts() - encoder2.Counts();
}

// Compute correction values based on error
void DriveStraight::computeCorrection(int error, int &correction1, int &correction2)
{
    correction1 = -kP * error;
    correction2 = kP * error;
}

// Apply motor power with correction
void DriveStraight::applyMotorCorrection(int targetSpeed, int correction1, int correction2)
{
    motor1.SetPercent(targetSpeed + correction1);
    motor2.SetPercent(targetSpeed + correction2);
}

// Main correction function
void DriveStraight::correctDriveStraight()
{
    int error = computeError();
    int correction1 = 0, correction2 = 0;

    computeCorrection(error, correction1, correction2);
    applyMotorCorrection(speed, correction1, correction2);
}

// Drive straight for a specified distance
void DriveStraight::driveStraight(float distance)
{
    resetEncoders();
    stopMotors();

    int targetCounts = inchesToCounts(distance) / cos(120 * M_PI / 180);

    motor1.SetPercent(speed);
    motor2.SetPercent(speed);

    while ((encoder1.Counts() + encoder2.Counts() / 2) <= targetCounts)
    {
        correctDriveStraight();
    }

    stopMotors();
}
