#include "include/logger.h"
#include "include/constants.h"
#include <FEHLCD.h>
#include <FEHUtility.h>

Logger::Logger(std::string name, bool enabled)
    : fileName(name), currentlyEnabled(enabled)
{
}

void Logger::logToSD(std::string msg)
{
    if (!currentlyEnabled)
    {
        return;
    }

    fptr = SD.FOpen(fileName.c_str(), "a");
    SD.FPrintf(fptr, "%s\n", msg.c_str());
    SD.FCloseAll();
}

void Logger::logToScreen(std::string msg)
{
    if (!currentlyEnabled)
    {
        return;
    }

    LCD.WriteLine(msg.c_str());
}

std::string Logger::getEncoderInfo()
{
    std::string encoderInfo = "Encoder A Counts: " + std::to_string(encoderA.Counts()) + "\n" +
                              "Encoder B Counts: " + std::to_string(encoderB.Counts()) + "\n" +
                              "Encoder C Counts: " + std::to_string(encoderC.Counts()) + "\n\n";
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