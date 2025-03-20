#include "include/constants.h"

Motor motorA = Motor(FEHMotor::Motor1, 9, FEHIO::P0_0, FEHIO::P0_1, true);
Motor motorB = Motor(FEHMotor::Motor2, 9, FEHIO::P2_0, FEHIO::P2_1);
Motor motorC = Motor(FEHMotor::Motor0, 9, FEHIO::P3_0, FEHIO::P3_1);

AnalogInputPin cdsCell(FEHIO::P3_7);