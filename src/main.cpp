#include <FEH.h>
#include "constants.h"
#include "utils.h"
#include "drive.h"

void ERCMain()
{
    // RCS.initialize("1240E4ZQS");
    // the servo needs to be configured in a main function,
    // so i just do it here
    servo.SetMin(500);
    servo.SetMax(2500);

    // Create drive system
    Drive drive = Drive();

    waitUntilTouch();
    Waypoint point;
    point.x = 10;
    point.y = 0;
    point.theta = 0;

    drive.driveToPosition(point, 25);

    // // Define waypoints for your course
    // const int WAYPOINT_COUNT = 3;
    // Waypoint course[WAYPOINT_COUNT] = {
    //     {24.0, 0.0, degToRad(0)},   // Start point
    //     {48.0, 12.0, degToRad(60)}, // Mid point
    //     {96.0, 36.0, 0.0}           // End point
    // };

    // for(int i = 0; i < 3; i++)
}