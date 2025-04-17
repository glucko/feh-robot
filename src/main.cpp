#include <FEH.h>
#include "constants.h"
#include "utils.h"
#include "drive.h"
#include "tasks.h"

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
    drive.driveToPosition({-1, -1});

    // Drive to Apple Bucket
    drive.driveToPosition({14, 10.5});
    pickUpBucket();

    // Drive to ramp
    drive.driveToPosition({6, -3});

    // Drive up ramp to table
    drive.driveUpRamp();

    // Drive to and hit button
    drive.driveToPosition({27, 20});

    // Drive to top of ramp
    drive.driveToPosition({30, -1});

    // Drive down ramp
    drive.driveDownRamp();

    // Drive to compost
    drive.driveToPosition({-5, 10});

    // Drive to start button
    drive.driveToPosition({-1, -1});
}