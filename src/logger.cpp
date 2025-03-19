#include <FEHLCD.h>
#include <FEHUtility.h>
#include "include/logger.h"
#include "include/constants.h"

Logger::Logger(float del, bool enabled)
    : delay(del), currentlyEnabled(enabled)
{
}

void Logger::logWithDelay(std::string msg)
{
    if (!currentlyEnabled || lastLogTime + delay > TimeNow())
    {
        return;
    }

    LCD.WriteLine(msg.c_str());
}

void Logger::log(std::string msg)
{
    if (!currentlyEnabled)
    {
        return;
    }

    LCD.WriteLine(msg.c_str());
}

std::string Logger::getEncoderInfo()
{
    std::string encoderInfo = "Encoder A Counts: " + std::to_string(motorA.Counts()) + "\n" +
                              "Encoder B Counts: " + std::to_string(motorB.Counts()) + "\n" +
                              "Encoder C Counts: " + std::to_string(motorC.Counts()) + "\n\n";
    return encoderInfo;
}

std::string Logger::getPrimaryEncoderInfo()
{
    std::string encoderInfo = "Primary Encoder A Counts: " + std::to_string(motorA.PrimaryCounts()) + "\n" +
                              "Primary Encoder B Counts: " + std::to_string(motorB.PrimaryCounts()) + "\n" +
                              "Primary Encoder C Counts: " + std::to_string(motorC.PrimaryCounts()) + "\n\n";
    return encoderInfo;
}

std::string Logger::getSecondaryEncoderInfo()
{
    std::string encoderInfo = "Secondary Encoder A Counts: " + std::to_string(motorA.SecondaryCounts()) + "\n" +
                              "Secondary Encoder B Counts: " + std::to_string(motorB.SecondaryCounts()) + "\n" +
                              "Secondary Encoder C Counts: " + std::to_string(motorC.SecondaryCounts()) + "\n\n";
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