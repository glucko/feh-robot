#ifndef MOTORFUNCTIONS_H
#define MOTORFUNCTIONS_H

void driveStraight(int distance);
void turn(int degrees);

void stopMotors();
void resetEncoders();

void inchToCounts(float inches);

#endif