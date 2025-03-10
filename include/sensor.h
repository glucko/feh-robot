#ifndef SENSOR_H
#define SENSOR_H

#include <FEHIO.h>
#include "motor.h"
#include "constants.h"

class Sensor
{
public:
    // Read the value of the cdsCell
    void cdsIsBlue(AnalogInputPin sensor, Motor motor1, Motor motor2, Motor motor3);
};

#endif // SENSOR_H
