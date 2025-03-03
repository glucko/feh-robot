#include "include/constants.h"
#include "include/motor.h"

// Motors (ports)
FEHMotor motorA_port(FEHMotor::Motor0, 9);
FEHMotor motorB_port(FEHMotor::Motor1, 9);
FEHMotor motorC_port(FEHMotor::Motor2, 9);

// Encoders (definitions)
DigitalEncoder encoderA(FEHIO::P0_0);
DigitalEncoder encoderB(FEHIO::P0_1);
DigitalEncoder encoderC(FEHIO::P0_2);

// Motor & Encoder wrapper class
Motor motorA = Motor(motorA_port, encoderA);
Motor motorB = Motor(motorA_port, encoderB);
Motor motorC = Motor(motorA_port, encoderC);

// humidifier
AnalogInputPin cdsCell(FEHIO::P1_1);
