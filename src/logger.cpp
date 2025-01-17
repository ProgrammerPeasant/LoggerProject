#include "../include/logger.h"
#include "../include/time_utils.h"
#include <fstream>
#include <iostream>

Logger::Logger(const Config &config)
    : logFileName(config.logFileName), defaultLevel(config.defaultLevel) {
    std::cout << "Opening file: " << logFileName << std::endl;
    std::ofstream logFile(logFileName, std::ios::app);
    if (!logFile) {
        std::cerr << "Failed to open log file!" << std::endl;
        throw std::runtime_error("Failed to open log file: " + logFileName);
    } else {
        std::cout << "File opened successfully." << std::endl;
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
    std::cout << "Attempting to write message: " << formattedMessage << std::endl;
    std::ofstream logFile(logFileName, std::ios::app);
    if (!logFile) {
        std::cerr << "Failed to open log file: " + logFileName << std::endl;
        return;
    }
    logFile << formattedMessage << std::endl;
    logFile.flush();
    std::cout << "Message written successfully." << std::endl;
}

int main() {
    Config config{R"(../app.log)", LogLevel::Info};
    Logger logger(config);

    // Логирование сообщений
    logger.log("This is a debug message", LogLevel::Debug); // Не запишется
    logger.log("This is an info message", LogLevel::Info);  // Запишется
    logger.log("This is an error message", LogLevel::Error); // Запишется

    // Изменение уровня важности
    logger.setLogLevel(LogLevel::Debug);
    logger.log("This is another debug message", LogLevel::Debug); // Теперь запишется



    return 0;
}