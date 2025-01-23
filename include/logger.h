#ifndef LOGGERPROJECT_LOGGER_H
#define LOGGERPROJECT_LOGGER_H

#include <string>
#include "log_level.h"
#include "config.h"

class Logger {
public:
    explicit Logger(const Config& config);
    void log(const std::string& message, LogLevel level);
    void setLogLevel(LogLevel level);

private:
    std::string logFileName;
    LogLevel defaultLevel;
    void writeToLog(const std::string& formattedMessage);
};

#endif //LOGGERPROJECT_LOGGER_H
