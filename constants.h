#include "FEHMotor.h"
#include "FEHIO.h"

#if !defined(CONSTANTS_H)
#define CONSTANTS_H

// Robot related
const float ROBOT_DIAMETER = 5;
const float WHEEL_DIAMETER = 2.5;

// Motors
FEHMotor motorA(FEHMotor::Motor0, 9);
FEHMotor motorB(FEHMotor::Motor1, 9);
FEHMotor motorC(FEHMotor::Motor2, 9);

// Encoders
DigitalEncoder encoderA(FEHIO::P0_0);
DigitalEncoder encoderB(FEHIO::P0_1);
DigitalEncoder encoderC(FEHIO::P0_2);

const int COUNTS_PER_ENCODER = 318;

// Speeds
const int NORMAL_POWER = 25;

#endif