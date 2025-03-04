#include "include/motor.h"
#include <FEHBattery.h>

Motor::Motor(FEHMotor::FEHMotorPort motorPort, int voltage, FEHIO::FEHIOPin encoderPort, bool r, float a)
    : motor(motorPort, voltage), encoder(encoderPort), reversed(r), adjustment(a)
{
}

void Motor::stopAndReset()
{
    motor.SetPercent(0);
    encoder.ResetCounts();
}

void Motor::SetPercent(int power)
{
    // adjusts based on motor differences
    int adjustedPower = power * adjustment;

    // adjusts based on battery voltage
    adjustedPower = 11.5 / Battery.Voltage() * adjustedPower;

    if (reversed)
    {
        adjustedPower = -adjustedPower;
    }

    motor.SetPercent(adjustedPower);
}

int Motor::Counts()
{
    return encoder.Counts();
}