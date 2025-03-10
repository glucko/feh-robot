#include "include/constants.h"

Motor motorA = Motor(FEHMotor::Motor1, 9, FEHIO::P0_0, true);
Motor motorB = Motor(FEHMotor::Motor0, 9, FEHIO::P2_0);
Motor motorC = Motor(FEHMotor::Motor2, 9, FEHIO::P1_0);

AnalogInputPin cdsCell(FEHIO::P3_1);