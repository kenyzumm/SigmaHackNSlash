#include "Logger.h"
#include <iostream>
#include <ctime>
#include <iomanip>

Logger::Logger(const std::string& filename) : logFile(filename, std::ios_base::app) {
    if (!logFile) {
        std::cerr << "Nie można otworzyć pliku logu!" << std::endl;
    }
    levelNames = {
        {Level::DEBUG, "DEBUG"},
        {Level::INFO, "INFO"},
        {Level::WARNING, "WARNING"},
        {Level::ERROR, "ERROR"},
        {Level::CRITICAL, "CRITICAL"}
    };
}

void Logger::log(Level level, const std::string& message) {
    if (!logFile) return;
    if (!shouldLog(level)) return;
    std::lock_guard<std::mutex> lock(mutex);

    std::time_t now = std::time(nullptr);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    logFile << "[" << buf << "] [" << levelNames[level] << "] " << message << std::endl;
}

void Logger::setLevel(Level newLevel) {
    minLevel = newLevel;
}

bool Logger::shouldLog(Level level) const {
    return level >= minLevel;
}