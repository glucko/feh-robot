#ifndef DRIVE_STRAIGHT_H
#define DRIVE_STRAIGHT_H

#include <FEHMotor.h>
#include <FEHIO.h>
#include <math.h>
#include "utils.h"

class DriveStraight
{
private:
    float kP;                 // Proportional correction factor
    int speed;                // Motor power percentage for speed
    FEHMotor &motorA;         // Reference to first active motor
    FEHMotor &motorB;         // Reference to second active motor
    DigitalEncoder &encoderA; // Reference to first active encoder
    DigitalEncoder &encoderB; // Reference to second active encoder

    // Compute encoder error between two wheels
    int computeError()
    {
        return encoderA.Counts() - encoderB.Counts();
    }

    // Compute correction values based on error
    void computeCorrection(int error, int &correction1, int &correction2)
    {
        correction1 = -kP * error;
        correction2 = kP * error;
    }

    // Apply motor power with correction
    void applyMotorCorrection(int targetSpeed, int correction1, int correction2)
    {
        motorA.SetPercent(targetSpeed + correction1);
        motorB.SetPercent(targetSpeed + correction2);
    }

    // Main correction function
    void correctDriveStraight()
    {
        int error = computeError();
        int correction1 = 0, correction2 = 0;

        computeCorrection(error, correction1, correction2);
        applyMotorCorrection(speed, correction1, correction2);
    }

public:
    // Constructor takes in references to the two active motors and encoders
    DriveStraight(FEHMotor &m1, FEHMotor &m2, DigitalEncoder &e1, DigitalEncoder &e2, float correctionFactor = 0.5, int s1 = 25)
        : motorA(m1), motorB(m2), encoderA(e1), encoderB(e2), kP(correctionFactor), speed(s1) {}

    void driveStraight(float distance)
    {
        resetEncoders();
        stopMotors();

        int targetCounts = inchesToCounts(distance) / cos(120 * M_PI / 180);

        motorA.SetPercent(speed);
        motorB.SetPercent(speed);

        while ((encoderA.Counts() + encoderB.Counts() / 2) <= targetCounts)
        {
            correctDriveStraight();
        }

        stopMotors();
    }
};

#endif