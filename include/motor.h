#ifndef MOTOR_H
#define MOTOR_H

#include <FEHMotor.h>
#include <FEHIO.h>

class Motor
{
private:
    FEHMotor &motor;
    DigitalEncoder &encoder;
    bool reversed;
    float adjustment;

public:
    Motor(FEHMotor &m, DigitalEncoder &e, bool reversed = false, float adjustment = 1.0);

    void stopAndReset();
    void setPower(int power);
    int getCounts();
};

#endif // MOTOR_H
