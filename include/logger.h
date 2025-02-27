#ifndef LOGGER_H
#define LOGGER_H

#include <FEHSD.h>
#include <string>

class Logger
{
private:
    std::string fileName;
    FEHFile *fptr;
    bool overwriteFile;
    bool currentlyEnabled;
    float lastFlushTime;

    void openLogger();
    void printToFile(std::string msg);
    void printToScreen(std::string msg);

    void flushLogger();

public:
    // Constructor
    Logger(std::string name, bool overwriteFile = true, bool currentlyEnabled = true);

    void log(std::string msg, bool logToScreen);
    void closeLogger();
    void logEncoderInfo(bool logToScreen);

    void turnLoggerOn();
    void turnLoggerOff();
};

#endif // LOGGER_H
