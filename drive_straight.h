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

    int computeError();                                                           // Compute encoder error between two wheels
    void computeCorrection(int error, int &correction1, int &correction2);        // Compute correction values based on error
    void applyMotorCorrection(int targetSpeed, int correction1, int correction2); // Apply motor power with correction
    void correctDriveStraight();                                                  // Main correction function
    void resetEncoders();                                                         // Add method declaration
    void stopMotors();                                                            // Add method declaration
    int inchesToCounts(float inches);                                             // Add method declaration

public:
    // Constructor
    DriveStraight(FEHMotor &m1, FEHMotor &m2, DigitalEncoder &e1, DigitalEncoder &e2, float correctionFactor = 0.5, int s1 = 25);

    void driveStraight(float distance); // Drive straight for a specified distance
};

#endif // DRIVE_STRAIGHT_H
