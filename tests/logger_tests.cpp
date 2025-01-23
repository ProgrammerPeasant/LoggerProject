#include "../include/logger.h"
#include <iostream>
#include <cassert>
#include <fstream>

// Функция для проверки содержимого файла
bool fileContains(const std::string& fileName, const std::string& content) {
    std::ifstream file(fileName);
    if (!file) return false;
    std::string line;
    while (std::getline(file, line)) {
        if (line.find(content) != std::string::npos) {
            return true;
        }
    }
    return false;
}

// Тест конструктора
void testConstructor() {
    Config config = {"test_log.txt", LogLevel::Info};
    Logger logger(config);
    std::cout << "Constructor test passed!" << std::endl;
}

// Тест записи сообщения
void testLogMessage() {
    Config config = {"test_log.txt", LogLevel::Info};
    Logger logger(config);

    logger.log("Test message", LogLevel::Info);
    assert(fileContains("test_log.txt", "Test message"));

    std::cout << "LogMessage test passed!" << std::endl;
}

// Тест игнорирования сообщений ниже уровня
void testIgnoreLowLevelMessages() {
    Config config = {"test_log.txt", LogLevel::Info};
    Logger logger(config);

    logger.log("Ignored message", LogLevel::Debug);
    logger.log("Logged message", LogLevel::Info);

    assert(!fileContains("test_log.txt", "Ignored message"));
    assert(fileContains("test_log.txt", "Logged message"));

    std::cout << "IgnoreLowLevelMessages test passed!" << std::endl;
}

// Тест изменения уровня логирования
void testSetLogLevel() {
    Config config = {"test_log.txt", LogLevel::Info};
    Logger logger(config);

    logger.setLogLevel(LogLevel::Error);
    logger.log("Ignored message", LogLevel::Debug);
    logger.log("Logged message", LogLevel::Error);

    assert(!fileContains("test_log.txt", "Ignored message"));
    assert(fileContains("test_log.txt", "Logged message"));

    std::cout << "SetLogLevel test passed!" << std::endl;
}

int main() {
    testConstructor();
    testLogMessage();
    testIgnoreLowLevelMessages();
    testSetLogLevel();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
