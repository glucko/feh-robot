#include "include/constants.h"

Motor motorA = Motor(FEHMotor::Motor2, 9, FEHIO::P0_7, true);
Motor motorB = Motor(FEHMotor::Motor0, 9, FEHIO::P0_2);
Motor motorC = Motor(FEHMotor::Motor1, 9, FEHIO::P0_0);

AnalogInputPin cdsCell(FEHIO::P1_1);