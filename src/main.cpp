#include <FEH.h>
#include "constants.h"
#include "utils.h"

void ERCMain()
{
    servo.SetMin(500);
    servo.SetMax(2500);

    waitUntilTouch();
}