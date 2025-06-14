UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CXX := g++
else ifeq ($(UNAME_S),Darwin)
	CXX := clang++
else ifeq ($(UNAME_S),Windows_NT)
	CXX := g++
endif
CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++17
SRC_DIR := src
BUILD_DIR := build
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
TARGET := game
ifeq ($(OS),Windows_NT)
    MKDIR := mkdir $(BUILD_DIR) 2>nul || echo ""
    RM := del /Q $(BUILD_DIR)\* && rmdir $(BUILD_DIR)
else
    MKDIR := mkdir -p $(BUILD_DIR)
    RM := rm -rf $(BUILD_DIR) $(TARGET)
endif
all: $(BUILD_DIR) $(TARGET)
$(BUILD_DIR):
	$(MKDIR)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -Iinclude -o $@ $^
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -Iinclude -o $@
clean:
	$(RM)
.PHONY: all clean
