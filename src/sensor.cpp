#include <math.h>
#include "include/sensor.h"
#include "include/utils.h"
#include "include/constants.h"
#include "include/drive.h"
#include "include/motor.h"

void Sensor::cdsIsBlue(AnalogInputPin sensor, Motor motor1, Motor motor2, Motor motor3){
    Drive drive = Drive(motor1, motor3, motor3);
    if(sensor.Value() > redThreshold){
        drive.driveDirection(4, Direction::RIGHT, 15);
    } else {
        drive.driveDirection(4, Direction::LEFT, 15);
    }
}