CC := g++
CFLAGS := -c -Wall -std=c++17
LFLAGS := -std=c++17

TARGET := 8086.exe
BUILD_DIR := build
SRC_DIR := src
OBJ_DIR := obj

SRCS := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp)
OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)
OBJJ := $(wildcard $(OBJ_DIR)/*.cpp.o)

$(BUILD_DIR)/$(TARGET): $(OBJJ)
	@echo $(OBJJ)
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	$(CC) $(OBJJ) -o $@ $(LFLAGS)

$(OBJ_DIR)/%.cpp.o: %.cpp
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $(OBJ_DIR)/$(notdir $@)