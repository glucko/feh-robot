#include "include/constants.h"

Motor motorA = Motor(FEHMotor::Motor0, 9, FEHIO::P0_0);
Motor motorB = Motor(FEHMotor::Motor1, 9, FEHIO::P0_1);
Motor motorC = Motor(FEHMotor::Motor2, 9, FEHIO::P0_2);

AnalogInputPin cdsCell(FEHIO::P1_1);