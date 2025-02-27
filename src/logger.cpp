#include "include/logger.h"
#include "include/constants.h"
#include <iostream>
#include <FEHLCD.h>
#include <FEHUtility.h>

Logger::Logger(std::string name, bool overwrite, bool enabled)
    : fileName(name), overwriteFile(overwrite), fptr(nullptr), currentlyEnabled(enabled)
{
    openLogger();
    lastFlushTime = TimeNow();
}

void Logger::openLogger()
{
    const char *mode = "a";
    if (overwriteFile)
    {
        fptr = SD.FOpen(fileName.c_str(), "w");
    }

    fptr = SD.FOpen(fileName.c_str(), mode);
}

void Logger::closeLogger()
{

    SD.FClose(fptr);
}

void Logger::printToFile(std::string msg)
{
    SD.FPrintf(fptr, "%s\n", msg.c_str());
}

void Logger::printToScreen(std::string msg)
{
    LCD.WriteLine(msg.c_str());
}

void Logger::log(std::string msg, bool logToScreen)
{
    if (!currentlyEnabled)
    {
        return;
    }

    printToFile(msg);

    if (logToScreen)
    {
        printToScreen(msg);
    }

    // flushes logger if hasnt been flushed in 2 sec
    // this makes sure the logs are actually written to the sd card
    // in case the proteus needs to be shut down early
    if (TimeNow() - lastFlushTime > 2)
    {
        flushLogger();
    }
}

void Logger::logEncoderInfo(bool logToScreen)
{
    std::string encoderInfo = "Encoder A Counts: " + std::to_string(encoderA.Counts()) + "\n" +
                              "Encoder B Counts: " + std::to_string(encoderB.Counts()) + "\n" +
                              "Encoder C Counts: " + std::to_string(encoderC.Counts()) + "\n\n";
    log(encoderInfo, logToScreen);
}

void Logger::turnLoggerOn()
{
    currentlyEnabled = true;
}

void Logger::turnLoggerOff()
{
    currentlyEnabled = false;
}

void Logger::flushLogger()
{
    closeLogger();
    openLogger();
}