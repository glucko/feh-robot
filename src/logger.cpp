#include <FEHLCD.h>
#include <FEHUtility.h>
#include "include/logger.h"
#include "include/constants.h"

Logger::Logger(float del, bool enabled)
    : delay(del), currentlyEnabled(enabled)
{
    lastLogTime = TimeNow();
}

void Logger::log(std::string msg)
{
    if (!currentlyEnabled || (TimeNow() - lastLogTime < delay))
    {
        return;
    }

    lastLogTime = TimeNow();
    LCD.WriteLine(msg.c_str());
}

std::string Logger::getEncoderInfo()
{
    std::string encoderInfo = "Encoder A Counts: " + std::to_string(motorA.Counts()) + "\n" +
                              "Encoder B Counts: " + std::to_string(motorB.Counts()) + "\n" +
                              "Encoder C Counts: " + std::to_string(motorC.Counts()) + "\n\n";
    return encoderInfo;
}

void Logger::turnLoggerOn()
{
    currentlyEnabled = true;
}

void Logger::turnLoggerOff()
{
    currentlyEnabled = false;
}