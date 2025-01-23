# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -fPIC

# Папки
INCLUDE_DIR = include
SRC_DIR = src
MAIN_DIR = main
TESTS_DIR = tests
BUILD_DIR = ./build
BIN_DIR = $(BUILD_DIR)/bin
LIB_DIR = $(BUILD_DIR)/lib
OBJ_DIR = $(BUILD_DIR)/obj

# Файлы
LIB_SRC = $(SRC_DIR)/logger.cpp $(SRC_DIR)/time_utils.cpp
LIB_OBJ = $(LIB_SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
LIB_TARGET = $(LIB_DIR)/liblogger.so

MAIN_SRC = $(MAIN_DIR)/main.cpp
MAIN_OBJ = $(OBJ_DIR)/main.o
MAIN_TARGET = $(BIN_DIR)/logger

TEST_SRC = $(TESTS_DIR)/logger_tests.cpp
TEST_OBJ = $(OBJ_DIR)/logger_tests.o
TEST_TARGET = $(BIN_DIR)/logger_tests

# Цели
.PHONY: all clean build test

all: build $(MAIN_TARGET)

build:
	@mkdir -p $(BIN_DIR) $(LIB_DIR) $(OBJ_DIR)

# Сборка динамической библиотеки
$(LIB_TARGET): $(LIB_OBJ)
	$(CXX) -shared -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Сборка приложения
$(MAIN_TARGET): $(MAIN_OBJ) $(LIB_TARGET)
	$(CXX) $< -o $@ -L$(LIB_DIR) -Wl,-rpath,$(LIB_DIR) -llogger -pthread

$(MAIN_OBJ): $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Сборка тестов
$(TEST_TARGET): $(TEST_OBJ) $(LIB_TARGET)
	$(CXX) $^ -o $@ -L$(LIB_DIR) -Wl,-rpath,$(LIB_DIR) -llogger -pthread

$(TEST_OBJ): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Тесты
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Очистка
clean:
	@rm -rf $(BUILD_DIR)
