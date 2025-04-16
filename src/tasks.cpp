#include <FEH.h>
#include "drive.h"
#include "constants.h"
#include "utils.h"
#include "tasks.h"

Drive drive = Drive();

void pickUpBucket()
{

    servoLeveling(96);
    drive.driveToPosition({11, 15});
    servoLeveling(0);

    logger.log("Picked up Bucket");
}

void dropOffBucket()
{

    servoLeveling(90);

    Sleep(1.0);

    logger.log("finished dropOffBucket()");

    servoLeveling(0);
    Sleep(.5);
}

void flipFertilizerDown()
{

    servoLeveling(SERVO_LOWERED + 5);
    servoLeveling(0);

    logger.log("finished flipFertilizer()");
}

void hitButton()
{
}

void pushWindow()
{
}

// void driveToCompostFromStart()
// {
//     // Making pseudocode for Benjamin

//     // Set servo to vertical position
//     servo.SetDegree(0);
//     // Drive forward a bit from the button
//     drive.driveDirection(9, Direction::AB);
//     // Turn left to drive towards composter
//     drive.turn(16);

//     // Drive forward til in range of composter
//     drive.driveDirection(9, Direction::CA);
//     // Turn to make arm face composter
//     drive.turn(-157);
//     drive.driveDirection(-0.5, Direction::AB);

//     int numFlips = 0;
//     // Repeat until fully spinned one way
//     while (numFlips < 4)
//     {
//         servoLeveling(0);
//         drive.driveDirection(3.5, Direction::AB);
//         servoLeveling(150);
//         drive.driveDirection(-3.5, Direction::AB);
//         numFlips++;
//     }
//     numFlips = 0;

//     // Rotating back to original position (BONUS)
//     // Now do the same thing but set servo to lowest possible position, then rotate up instead of down
//     while (numFlips < 4)
//     {
//         servoLeveling(160);
//         drive.driveDirection(4.2, Direction::AB);
//         servoLeveling(0);
//         drive.driveDirection(-4, Direction::AB);
//         numFlips++;
//     }
// }

// void spinCompost()
// {
//     int numFlips = 0;
//     // Repeat until fully spinned one way
//     while (numFlips < 4)
//     {
//         servoLeveling(0);
//         drive.driveDirection(3.5, Direction::AB);
//         servoLeveling(150);
//         drive.driveDirection(-3.5, Direction::AB);
//         numFlips++;
//     }
//     numFlips = 0;
// }