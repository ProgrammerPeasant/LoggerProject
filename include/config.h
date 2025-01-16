#ifndef LOGGERPROJECT_CONFIG_H
#define LOGGERPROJECT_CONFIG_H

#include "log_level.h"
#include <string>

struct Config {
    std::string logFileName;
    LogLevel defaultLevel;
};

#endif //LOGGERPROJECT_CONFIG_H
