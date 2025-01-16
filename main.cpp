#include "include/logger.h"
#include "include/log_level.h"


int main() {
    Config config{R"(..\app.log)", LogLevel::Info};
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
