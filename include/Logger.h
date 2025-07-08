#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <mutex>
#include <map>

// Class responsible for logging to a file with different log levels
class Logger {
public:
    // Log levels (DEBUG, INFO, WARNING, ERROR, CRITICAL)
    enum class Level {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        CRITICAL
    };

    // Creates a logger and opens the log file
    explicit Logger(const std::string& filename);
    // Writes a message to the log at a given level
    void log(Level level, const std::string& message);
    // Sets the minimum log level
    void setLevel(Level newLevel);
    // Checks if a given level should be logged
    bool shouldLog(Level level) const;

private:
    std::ofstream logFile; // Stream for the log file
    std::mutex mutex;      // Mutex for synchronization
    std::map<Level, std::string> levelNames; // Names of log levels
    Level minLevel = Level::DEBUG; // Minimum log level
};

// Macros for easier logging at different levels
#define LOG_DEBUG(logger, message)    if((logger).shouldLog(Logger::Level::DEBUG))    (logger).log(Logger::Level::DEBUG, message)
#define LOG_INFO(logger, message)     if((logger).shouldLog(Logger::Level::INFO))     (logger).log(Logger::Level::INFO, message)
#define LOG_WARNING(logger, message)  if((logger).shouldLog(Logger::Level::WARNING))  (logger).log(Logger::Level::WARNING, message)
#define LOG_ERROR(logger, message)    if((logger).shouldLog(Logger::Level::ERROR))    (logger).log(Logger::Level::ERROR, message)
#define LOG_CRITICAL(logger, message) if((logger).shouldLog(Logger::Level::CRITICAL)) (logger).log(Logger::Level::CRITICAL, message)
// Each macro checks the log level and calls log() only if the level is active

#endif // LOGGER_H
