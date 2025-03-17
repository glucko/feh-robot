#ifndef LOGGER_H
#define LOGGER_H

#include <FEHSD.h>
#include <string>

class Logger
{
private:
    float delay;
    float lastLogTime;
    bool currentlyEnabled;

public:
    Logger(float del = .1f, bool currentlyEnabled = true);

    std::string getEncoderInfo();
    void log(std::string msg);
    void turnLoggerOff();
    void turnLoggerOn();
};

#endif // LOGGER_H
