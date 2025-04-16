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
    // Drive to start button
    drive.driveToPosition({-2, -1});

    // Drive to Apple Bucket
    drive.driveToPosition({10, 13});

    // Drive to ramp
    drive.driveToPosition({6, -1});

    // Drive up ramp to table
    drive.turn(-120 * DEG_TO_RAD);
    drive.driveUpRamp();

    // Drive to window
    drive.driveToPosition({22, 5});

    // Open window
    drive.driveToPosition({25, 15});

    // Drive to and hit button
    drive.driveToPosition({27, 20});

    // Drive to top of ramp
    drive.driveToPosition({30, -1});

    // Drive down ramp
    drive.driveToPosition({6, -1});

    // Drive to compost
    drive.driveToPosition({-5, 10});

    // Drive to start button
    drive.driveToPosition({-2, -1});
}