TARGET = app

SRC_DIR = src
BUILD_DIR = build
TEST_DIR = tests
#GTEST_DIR =

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Подключение Google Test
#GTEST_LIBS = -lgtest -lgtest_main -pthread
#GTEST_FLAGS = -I$(GTEST_DIR)/include -L$(GTEST_DIR)/lib

.PHONY: all build clean test

all: build

build: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: build $(BUILD_DIR)/tests
	@echo "Running tests..."
	$(BUILD_DIR)/tests

$(BUILD_DIR)/tests: $(TEST_OBJS) $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(GTEST_FLAGS) -o $@ $^ $(GTEST_LIBS)

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)
