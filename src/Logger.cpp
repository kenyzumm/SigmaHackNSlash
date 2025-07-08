#include "Logger.h"
#include <iostream>
#include <ctime>
#include <iomanip>

// Constructor: opens the log file and sets the level map
Logger::Logger(const std::string& filename) : logFile(filename, std::ios_base::app) {
    if (!logFile) {
        std::cerr << "Cannot open log file!" << std::endl;
    }
    levelNames = {
        {Level::DEBUG, "DEBUG"},
        {Level::INFO, "INFO"},
        {Level::WARNING, "WARNING"},
        {Level::ERROR, "ERROR"},
        {Level::CRITICAL, "CRITICAL"}
    };
}

// Writes a message to the log file at a given level
void Logger::log(Level level, const std::string& message) {
    if (!logFile) return;
    if (!shouldLog(level)) return;
    std::lock_guard<std::mutex> lock(mutex); // Ensures thread safety

    std::time_t now = std::time(nullptr);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    logFile << "[" << buf << "] [" << levelNames[level] << "] " << message << std::endl;
}

// Sets the minimum log level
void Logger::setLevel(Level newLevel) {
    minLevel = newLevel;
}

// Checks if a given level should be logged
bool Logger::shouldLog(Level level) const {
    return level >= minLevel;
}