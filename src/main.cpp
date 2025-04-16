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
    drive.driveToPosition({-2, -1, 0}, 25);

    // Drive to Apple Bucket
    drive.driveToPosition({10, 13, 0}, 25);
    drive.turn(120);


    // Drive to ramp
    drive.driveToPosition({6, -1, 0}, 25);

    // Drive up ramp to table
    drive.driveToPosition({30, -2, 0}, 40, true);

    // Drive to window
    drive.driveToPosition({22, 5, 0}, 25);

    // Open window
    drive.driveToPosition({25, 15, 0}, 25);

    // Drive to and hit button
    drive.driveToPosition({27, 20, 0}, 25);

    // Drive to top of ramp
    drive.driveToPosition({30, -1, 0}, 25);

    // Drive down ramp
    drive.driveToPosition({6, -1, 0}, 25);

    // Drive to compost
    drive.driveToPosition({-5, 10, 0}, 25);

    // Drive to start button
    drive.driveToPosition({-2, -1, 0}, 25);

    /*drive.driveToPosition({-2, -1, 0}, 25);
    drive.driveToPosition({10, 15, 0}, 25);
    drive.driveToPosition({10, 0, 0}, 25);
    drive.driveToPosition({30, 0, 0}, 35);*/
}