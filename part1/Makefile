# Makefile for Part 1 – Static Convex Hull

CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra -O2

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = ..
PART1_TARGET = $(BIN_DIR)/ch_part1

# Test file
TEST_FILE = ../test_part1.txt

# Source files
PART1_SRCS = $(SRC_DIR)/main.cpp \
             $(SRC_DIR)/geom/Hull.cpp

.PHONY: all clean run valgrind

all: $(PART1_TARGET)

$(PART1_TARGET): $(PART1_SRCS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Run using test file
run: $(PART1_TARGET)
	$(PART1_TARGET) < $(TEST_FILE)

# Valgrind check
valgrind: $(PART1_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all $(PART1_TARGET) < $(TEST_FILE)

clean:
	rm -f $(PART1_TARGET) *.o
