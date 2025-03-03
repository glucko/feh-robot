#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <FEHIO.h>
#include <FEHMotor.h>

// Robot related
const float ROBOT_DIAMETER = 5;
const float WHEEL_DIAMETER = 2.5;

// Motors (declarations)
extern Motor motorA;
extern Motor motorB;
extern Motor motorC;

const int COUNTS_PER_ENCODER = 318;

// Speeds
const int NORMAL_POWER = 25;

extern AnalogInputPin cdsCell;
const float redThreshold = .39;
const float noLight = 1;

const enum Direction {
    LEFT = -1,
    FORWARD = 0,
    RIGHT = 1
};

#endif
