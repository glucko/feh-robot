#include <FEHLCD.h>
#include <FEHUtility.h>
#include "logger.h"
#include "constants.h"

Logger::Logger(float del, bool enabled)
    : delay(del), currentlyEnabled(enabled)
{
}

void Logger::logWithDelay(String msg)
{
    if (!currentlyEnabled || lastLogTime + delay > TimeNow())
    {
        return;
    }

    lastLogTime = TimeNow();
    LCD.WriteLine(msg.c_str());
}

void Logger::log(String msg)
{
    if (!currentlyEnabled)
    {
        return;
    }

    LCD.WriteLine(msg.c_str());
    Serial.println(msg);
}

String Logger::getEncoderInfo()
{
    String encoderInfo = "Encoder A Counts: " + String(motorA.Counts()) + "\n" +
                         "Encoder B Counts: " + String(motorB.Counts()) + "\n" +
                         "Encoder C Counts: " + String(motorC.Counts()) + "\n\n";
    return encoderInfo;
}

String Logger::getPrimaryEncoderInfo()
{
    String encoderInfo = "Primary Encoder A Counts: " + String(motorA.PrimaryCounts()) + "\n" +
                         "Primary Encoder B Counts: " + String(motorB.PrimaryCounts()) + "\n" +
                         "Primary Encoder C Counts: " + String(motorC.PrimaryCounts()) + "\n\n";
    return encoderInfo;
}

String Logger::getSecondaryEncoderInfo()
{
    String encoderInfo = "Secondary Encoder A Counts: " + String(motorA.SecondaryCounts()) + "\n" +
                         "Secondary Encoder B Counts: " + String(motorB.SecondaryCounts()) + "\n" +
                         "Secondary Encoder C Counts: " + String(motorC.SecondaryCounts()) + "\n\n";
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