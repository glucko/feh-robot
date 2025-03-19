/**
 * @file logger.h
 * @brief Header file for the Logger class, which provides functionality for logging messages and encoder information with a configurable delay.
 *
 * This file defines the Logger class, including its methods for enabling/disabling logging,
 * retrieving encoder information, and logging messages. The Logger class is designed to
 * facilitate debugging and data recording in applications that require periodic logging.
 *
 * @author Benjamin Gluck
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <string>

/**
 * @class Logger
 * @brief A class for logging messages and encoder information with a configurable delay.
 */
class Logger
{
private:
    float delay;                /**< The delay between log messages in seconds. */
    float lastLogTime = -100.0; /**< The timestamp of the last log message. Set to a negative number so the first message has no delay. */
    bool currentlyEnabled;      /**< Indicates whether the logger is currently enabled. */

public:
    /**
     * @brief Constructs a Logger object with a specified delay and enabled state.
     * @param del The delay between log messages in seconds (default is 0.1f).
     * @param currentlyEnabled Whether the logger is initially enabled (default is true).
     */
    Logger(float del = .1f, bool currentlyEnabled = true);

    /**
     * @brief Retrieves information about the encoders.
     * @return A string containing the encoder information.
     */
    std::string getEncoderInfo();

    /**
     * @brief Retrieves information about the primary encoders.
     * @return A string containing the encoder information.
     */
    std::string getPrimaryEncoderInfo();

    /**
     * @brief Retrieves information about the secondary encoders.
     * @return A string containing the encoder information.
     */
    std::string getSecondaryEncoderInfo();

    /**
     * @brief Logs a message.
     * @param msg The message to be logged.
     */
    void log(std::string msg);

    /**
     * @brief Logs a message with a delay, should only be used once in the code as the delay is global.
     * @param msg The message to be logged.
     */
    void logWithDelay(std::string msg);

    /**
     * @brief Disables the logger, preventing further logging.
     */
    void turnLoggerOff();

    /**
     * @brief Enables the logger, allowing logging to resume.
     */
    void turnLoggerOn();
};

#endif // LOGGER_H
