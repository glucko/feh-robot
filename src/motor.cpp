#include "include/motor.h"
#include <FEHBattery.h>

Motor::Motor(FEHMotor &m, DigitalEncoder &e, bool r, float a)
    : motor(m), encoder(e), reversed(r), adjustment(a)
{
}

void Motor::stopAndReset()
{
    motor.SetPercent(0);
    encoder.ResetCounts();
}

void Motor::setPower(int power)
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

int Motor::getCounts()
{
    return encoder.Counts();
}