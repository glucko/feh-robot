#ifndef MOTOR_H
#define MOTOR_H

#include <FEHMotor.h>
#include <FEHIO.h>

class Motor
{
private:
    FEHMotor motor;
    DigitalEncoder encoder;
    bool reversed;
    float adjustment;

public:
    Motor(FEHMotor::FEHMotorPort motorPort, int voltage, FEHIO::FEHIOPin encoderPort, bool reversed = false, float adjustment = 1.0);

    // Stops the motor and resets encoder
    void stopAndReset();

    // Sets motor to specified power, accounting for motor-specific correction and voltage correction
    void SetPercent(int power);

    // Returns number of encoder counts
    int Counts();
};

#endif // MOTOR_H
