#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include "logger.h"

// Потокобезопасная очередь
class ThreadSafeQueue {
public:
    void push(const std::pair<std::string, LogLevel>& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(item);
        condVar_.notify_one();
    }

    bool pop(std::pair<std::string, LogLevel>& item) {
        std::unique_lock<std::mutex> lock(mutex_);
        condVar_.wait(lock, [this]() { return !queue_.empty(); });
        item = queue_.front();
        queue_.pop();
        return true;
    }

private:
    std::queue<std::pair<std::string, LogLevel>> queue_;
    std::mutex mutex_;
    std::condition_variable condVar_;
};

// Глобальная очередь и флаг завершения работы
ThreadSafeQueue logQueue;
bool isRunning = true;

// Поток записи в лог
void loggerThread(Logger& logger) {
    while (isRunning) {
        std::pair<std::string, LogLevel> logEntry;
        if (logQueue.pop(logEntry)) {
            logger.log(logEntry.first, logEntry.second);
        }
    }
}

// Функция для получения уровня важности из строки
LogLevel parseLogLevel(const std::string& input) {
    if (input == "info") return LogLevel::Info;
    if (input == "debug") return LogLevel::Debug;
    if (input == "error") return LogLevel::Error;
    return LogLevel::Info; // Уровень по умолчанию
}

int main(int argc, char* argv[]) {
    // Проверяем параметры запуска
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <log_file> <default_log_level>" << std::endl;
        return 1;
    }

    std::string logFileName = argv[1];
    LogLevel defaultLogLevel = parseLogLevel(argv[2]);

    // Инициализация логгера
    Config config = {logFileName, defaultLogLevel};
    Logger logger(config);

    // Запуск потока логгера
    std::thread logThread(loggerThread, std::ref(logger));

    // Цикл пользовательского ввода
    while (true) {
        std::string input;
        std::cout << "Enter message (or 'exit' to quit): ";
        std::getline(std::cin, input);

        if (input == "exit") {
            isRunning = false;
            logQueue.push({"", LogLevel::Info}); // "Будит" поток
            break;
        }

        // Опционально считываем уровень важности
        std::string levelInput;
        std::cout << "Enter log level (info/warning/error, default is info): ";
        std::getline(std::cin, levelInput);

        LogLevel level = parseLogLevel(levelInput);
        logQueue.push({input, level});
    }

    // Ждем завершения потока
    logThread.join();
    return 0;
}
