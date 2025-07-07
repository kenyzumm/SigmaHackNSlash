#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <mutex>
#include <map>

class Logger {
public:
    enum class Level {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        CRITICAL
    };

    explicit Logger(const std::string& filename);
    void log(Level level, const std::string& message);
    void setLevel(Level newLevel);
    bool shouldLog(Level level) const;

private:
    std::ofstream logFile;
    std::mutex mutex;
    std::map<Level, std::string> levelNames;
    Level minLevel = Level::DEBUG;
};

#define LOG_DEBUG(logger, message)    if((logger).shouldLog(Logger::Level::DEBUG))    (logger).log(Logger::Level::DEBUG, message)
#define LOG_INFO(logger, message)     if((logger).shouldLog(Logger::Level::INFO))     (logger).log(Logger::Level::INFO, message)
#define LOG_WARNING(logger, message)  if((logger).shouldLog(Logger::Level::WARNING))  (logger).log(Logger::Level::WARNING, message)
#define LOG_ERROR(logger, message)    if((logger).shouldLog(Logger::Level::ERROR))    (logger).log(Logger::Level::ERROR, message)
#define LOG_CRITICAL(logger, message) if((logger).shouldLog(Logger::Level::CRITICAL)) (logger).log(Logger::Level::CRITICAL, message)

#endif // LOGGER_H
