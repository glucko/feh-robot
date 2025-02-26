#include "constants.h"

// Motors (definitions)
FEHMotor motorA(FEHMotor::Motor0, 9);
FEHMotor motorB(FEHMotor::Motor1, 9);
FEHMotor motorC(FEHMotor::Motor2, 9);

// Encoders (definitions)
DigitalEncoder encoderA(FEHIO::P0_0);
DigitalEncoder encoderB(FEHIO::P0_1);
DigitalEncoder encoderC(FEHIO::P0_2);
