#include "../include/logger.h"
#include "../include/time_utils.h"
#include <fstream>
#include <iostream>

Logger::Logger(const Config &config)
    : logFileName(config.logFileName), defaultLevel(config.defaultLevel) {
    std::ofstream logFile(logFileName, std::ios::app);
    if (!logFile) {
        std::cerr << "Failed to open log file!" << std::endl;
        throw std::runtime_error("Failed to open log file: " + logFileName);
    }
}

void Logger::log(const std::string &message, LogLevel level) {
    if (level < defaultLevel) {
        return;
    }

    std::string formattedMessage = "[" + getCurrentTime() + "] ";
    formattedMessage += "[" + std::to_string(static_cast<int>(level)) + "] ";
    formattedMessage += message;

    writeToLog(formattedMessage);
}

void Logger::setLogLevel(LogLevel level) {
    defaultLevel = level;
}

void Logger::writeToLog(const std::string &formattedMessage) {
    std::ofstream logFile(logFileName, std::ios::app);
    if (!logFile) {
        std::cerr << "Failed to open log file: " + logFileName << std::endl;
        return;
    }
    logFile << formattedMessage << std::endl;
    logFile.flush();
}
