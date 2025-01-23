#ifndef LOGGERPROJECT_LOG_LEVEL_H
#define LOGGERPROJECT_LOG_LEVEL_H

enum class LogLevel {
    Debug,
    Info,
    Error
};

inline std::string logLevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::Debug: return "Debug";
        case LogLevel::Info: return "Info";
        case LogLevel::Error: return "Error";
        default: return "Unknown";
    }
}

#endif //LOGGERPROJECT_LOG_LEVEL_H
