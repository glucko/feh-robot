#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <FEHIO.h>
#include <FEHMotor.h>
#include "include/motor.h"

// Robot construction constants
const float ROBOT_DIAMETER = 5;
const float WHEEL_DIAMETER = 2.5;

// Motors
extern Motor motorA;
extern Motor motorB;
extern Motor motorC;

const int COUNTS_PER_ENCODER = 318;

// Speeds
const int NORMAL_POWER = 25;

extern AnalogInputPin cdsCell;
const float redThreshold = .39;
const float noLight = 1;

enum class Direction
{
    LEFT,
    FORWARD,
    RIGHT
};

#endif
