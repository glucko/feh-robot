#include <FEH.h>
#include <PID_v1.h>
#include "drive.h"
#include "utils.h"
#include "constants.h"
#include <pidautotuner.h>

const float SLEEPTIME = .5;

Drive::Drive(Motor &m1, Motor &m2, Motor &m3)
    : motor1(m1), motor2(m2), motor3(m3)
{
}

void Drive::driveWithMode(DriveMode mode, Direction direction, int power, float distance)
{
    resetAll();

    Motor *mot1;
    Motor *mot2;

    // Determines which motors will be turning based on direction
    switch (direction)
    {
    case Direction::AB:
        mot1 = &motor1;
        mot2 = &motor2;
        break;

    case Direction::BC:
        mot1 = &motor2;
        mot2 = &motor3;
        break;

    case Direction::CA:
        mot1 = &motor1;
        mot2 = &motor3;
        break;
    }

    double input = mot1->Counts() - mot2->Counts();
    double target = 0;
    double adjustedPower = power;

    PIDAutotuner tuner = PIDAutotuner();
    tuner.setTargetInputValue(0);
    int loopInterval = 100 * 100;
    tuner.setLoopInterval(loopInterval);
    tuner.setOutputRange(power - 10, power + 10);
    tuner.startTuningLoop(micros());

    long microseconds;
    while (!tuner.isFinished())
    {
        microseconds = micros();
        input = mot1->Counts() - mot2->Counts();
        double output = tuner.tunePID(input, microseconds);
        logger.log(String(output));

        mot1->SetPercent(output);
        mot2->SetPercent(-output);

        while (micros() - microseconds < loopInterval)
            delayMicroseconds(1);
    }

    // Get PID gains - set your PID controller's gains to these
    double kp = tuner.getKp();
    double ki = tuner.getKi();
    double kd = tuner.getKd();

    logger.log("kp: " + String(kp) + " ki: " + String(ki) + " kd: " + String(kd));
    resetAll();
}

// Wrapper functions to maintain original API
void Drive::driveDirection(float distance, Direction direction, int power)
{
    driveWithMode(DriveMode::DISTANCE, direction, power, distance);
}

void Drive::driveUntilLight(Direction direction, int power)
{
    driveWithMode(DriveMode::LIGHT, direction, power, 0);
}

void Drive::turn(float degrees, int power)
{
    resetAll();

    Motor *mot1 = &motor1;
    Motor *mot2 = &motor2;
    Motor *mot3 = &motor3;

    // If counterclockwise, invert the power
    if (degrees < 0)
    {
        power = -power;
        degrees = -degrees;
    }

    float arcLength = (ROBOT_DIAMETER / 2) * degToRad(degrees);

    double input = (mot1->Counts() + mot2->Counts() + mot3->Counts()) / 3;
    double target = inchesToCounts(arcLength);
    double adjustedPower = power;

    PID pid(&input, &adjustedPower, &target, 0, 0, 0, DIRECT);
    pid.SetMode(AUTOMATIC);

    while ((motor1.Counts() + motor2.Counts() + motor3.Counts()) / 3 < target)
    {
        input = (mot1->Counts() + mot2->Counts() + mot3->Counts()) / 3;
        pid.Compute();
        adjustedPower = constrain(adjustedPower, power - 5, power + 5);

        mot1->SetPercent(adjustedPower);
        mot2->SetPercent(adjustedPower);
        mot3->SetPercent(adjustedPower);
    }

    resetAll();

    Sleep(SLEEPTIME);
}