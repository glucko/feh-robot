#include "constants.h"

Motor motorA = Motor(FEHMotor::Motor1, 9, FEHIO::Pin12, FEHIO::Pin13);
Motor motorB = Motor(FEHMotor::Motor2, 9, FEHIO::Pin10, FEHIO::Pin11);
Motor motorC = Motor(FEHMotor::Motor0, 9, FEHIO::Pin8, FEHIO::Pin9);

AnalogInputPin cdsCell(FEHIO::Pin0);

FEHServo servo(FEHServo::Servo1);