#ifndef LOGGER_H
#define LOGGER_H

#include <FEHSD.h>
#include <string>

class Logger
{
private:
    std::string fileName;
    FEHFile *fptr;
    bool currentlyEnabled;

    void openLogger();
    void printToFile(std::string msg);
    void printToScreen(std::string msg);

public:
    Logger(std::string name, bool currentlyEnabled = true);

    // Logs message to SD card, automatically flushing the output
    void logToSD(std::string msg);
    void logToScreen(std::string msg);

    std::string getEncoderInfo();

    void turnLoggerOff();
    void turnLoggerOn();
};

#endif // LOGGER_H
