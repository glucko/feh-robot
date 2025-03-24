#include "motor.h"
#include <FEHUtility.h>

Motor::Motor(FEHMotor::FEHMotorPort motorPort, int voltage, FEHIO::FEHIOPin encoderPort, FEHIO::FEHIOPin encoderPortSecondary, bool r, float a)
    : motor(motorPort, voltage), encoder(encoderPort), encoderSecondary(encoderPortSecondary), reversed(r), adjustment(a)
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
    adjustedPower = 11.5 / BatteryVoltage() * adjustedPower;

    if (reversed)
    {
        adjustedPower = -adjustedPower;
    }

    motor.SetPercent(adjustedPower);
}

int Motor::Counts()
{
    return encoder.Counts() + encoderSecondary.Counts();
}

int Motor::PrimaryCounts()
{
    return encoder.Counts();
}

int Motor::SecondaryCounts()
{
    return encoderSecondary.Counts();
}