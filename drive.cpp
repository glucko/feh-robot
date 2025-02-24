#include <FEHMotor.h>
#include <constants.h>
#include <math.h>

void stopMotors()
{
    motorA.SetPercent(0);
    motorB.SetPercent(0);
    motorC.SetPercent(0);
}

void resetEncoders()
{
    encoderA.ResetCounts();
    encoderB.ResetCounts();
    encoderC.ResetCounts();
}

int inchesToCounts(float inches)
{
    return inches * COUNTS_PER_ENCODER / M_PI * WHEEL_DIAMETER;
}

void driveStraight(int distance)
{
    resetEncoders();

    int targetCounts = distance * COUNTS_PER_ENCODER;

    while ((encoderA.Counts() + encoderB.Counts() + encoderC.Counts() / 3) <= targetCounts)
    {
    }

    stopMotors();
}

void turn(int degrees)
{
    resetEncoders();

    float dist = (degrees * M_PI / 180) * ROBOT_DIAMETER / 2;
    int targetCounts = inchesToCounts(dist);

    motorA.SetPercent(NORMAL_POWER);
    motorB.SetPercent(-NORMAL_POWER);

    // waits until number of counts has been reached
    while ((encoderA.Counts() + encoderB.Counts() + encoderC.Counts() / 3) <= targetCounts)
    {
    }

    stopMotors();
}
