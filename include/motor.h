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

    void stopAndReset();
    void SetPercent(int power);
    int Counts();
};

#endif // MOTOR_H
