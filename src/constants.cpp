#include "constants.h"

Motor motorA = Motor(FEHMotor::Motor0, 9, FEHIO::Pin13, FEHIO::Pin14);
Motor motorB = Motor(FEHMotor::Motor1, 9, FEHIO::Pin9, FEHIO::Pin10);
Motor motorC = Motor(FEHMotor::Motor2, 9, FEHIO::Pin11, FEHIO::Pin12);

AnalogInputPin cdsCell(FEHIO::Pin8);

FEHServo servo(FEHServo::Servo1);