#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include "../include/logger.h"

// Хелпер-функция для чтения содержимого файла
std::string readFile(const std::string& fileName) {
    std::ifstream file(fileName);
    std::ostringstream content;
    content << file.rdbuf();
    return content.str();
}

// Тест на корректность конструктора
TEST(LoggerTest, Constructor) {
    Config config = {"test_log.txt", LogLevel::Info};
    EXPECT_NO_THROW(Logger logger(config));
}

// Тест записи сообщения в лог
TEST(LoggerTest, LogMessage) {
    std::string testFileName = "test_log.txt";
    Config config = {testFileName, LogLevel::Info};
    Logger logger(config);

    logger.log("Test message 1", LogLevel::Info);
    logger.log("Test message 2", LogLevel::Debug);

    std::string logContent = readFile(testFileName);
    EXPECT_NE(logContent.find("Test message 1"), std::string::npos);
    EXPECT_NE(logContent.find("Test message 2"), std::string::npos);

    // Удаляем файл после теста
    remove(testFileName.c_str());
}

// Тест игнорирования сообщений ниже уровня логирования
TEST(LoggerTest, IgnoreLowLevelMessages) {
    std::string testFileName = "test_log.txt";
    Config config = {testFileName, LogLevel::Debug};
    Logger logger(config);

    logger.log("This should be ignored", LogLevel::Info);
    logger.log("This should be logged", LogLevel::Debug);

    std::string logContent = readFile(testFileName);
    EXPECT_EQ(logContent.find("This should be ignored"), std::string::npos);
    EXPECT_NE(logContent.find("This should be logged"), std::string::npos);

    // Удаляем файл после теста
    remove(testFileName.c_str());
}

// Тест изменения уровня логирования
TEST(LoggerTest, SetLogLevel) {
    std::string testFileName = "test_log.txt";
    Config config = {testFileName, LogLevel::Info};
    Logger logger(config);

    logger.setLogLevel(LogLevel::Error);
    logger.log("This should be ignored", LogLevel::Debug);
    logger.log("This should be logged", LogLevel::Error);

    std::string logContent = readFile(testFileName);
    EXPECT_EQ(logContent.find("This should be ignored"), std::string::npos);
    EXPECT_NE(logContent.find("This should be logged"), std::string::npos);

    // Удаляем файл после теста
    remove(testFileName.c_str());
}
