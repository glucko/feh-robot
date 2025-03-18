#include "include/constants.h"

Motor motorA = Motor(FEHMotor::Motor0, 9, FEHIO::P0_0, FEHIO::P0_2);
Motor motorB = Motor(FEHMotor::Motor1, 9, FEHIO::P1_0, FEHIO::P1_1, true);
Motor motorC = Motor(FEHMotor::Motor2, 9, FEHIO::P3_0, FEHIO::P3_1);

AnalogInputPin cdsCell(FEHIO::P0_7);