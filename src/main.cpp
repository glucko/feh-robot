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

    drive.turn(180);
}