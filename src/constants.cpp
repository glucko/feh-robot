#include "include/constants.h"

// Motor & Encoder wrapper classes

// The motor marked with A, between the apple bucket and stick mechanisms
Motor motorA = Motor(FEHMotor::Motor0, 9, FEHIO::P0_0);

// The motor marked with B, between the compost and apple bucket mechanisms
Motor motorB = Motor(FEHMotor::Motor1, 9, FEHIO::P0_1);

// The motor marked with C, between the stick and compost mechanisms
Motor motorC = Motor(FEHMotor::Motor2, 9, FEHIO::P0_2);

// Humidifier detecting cell
AnalogInputPin cdsCell(FEHIO::P1_1);
