#ifndef DRIVE_H
#define DRIVE_H

#include <FEHIO.h>
#include "motor.h"
#include "constants.h"

class Drive
{
private:
    // Proportional correction factor
    float kP;
    Motor &motor1;
    Motor &motor2;
    Motor &motor3;

    // Main correction function
    // mot1 & mot2 are the motors that are currently driving
    void correctDriveStraight(Motor *mot1, Motor *mot2, int targetPower);

public:
    // Takes in the three motors of the robot
    // correctionFactor will adjust how aggressive the correction is, higher is more aggressive
    Drive(Motor &m1, Motor &m2, Motor &m3, float correctionFactor = 0.5);

    // Drive straight in direction for a specified distance (inches) at power
    void driveDirection(float distance, Direction direction, int power);
};

#endif // DRIVE_H
