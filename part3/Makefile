# Makefile for Part 3 – Interactive Convex Hull

CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra -O2

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = ..
PART3_TARGET = $(BIN_DIR)/ch_part3

# Test files (relative to part3)
VECTOR_TEST = ../test_part2_vector.txt
LIST_TEST   = ../test_part2_list.txt

# Source files
PART3_SRCS = $(SRC_DIR)/main.cpp \
             $(SRC_DIR)/core/State.cpp \
             $(SRC_DIR)/geom/Hull.cpp

.PHONY: all clean run run_vector run_list valgrind_vector valgrind_list

all: $(PART3_TARGET)

$(PART3_TARGET): $(PART3_SRCS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Run both tests (vector then list)
run: run_vector run_list

# Run with vector implementation test input
run_vector: $(PART3_TARGET)
	@echo "Running Vector Test..."
	$(PART3_TARGET) < $(VECTOR_TEST)

# Run with list implementation test input
run_list: $(PART3_TARGET)
	@echo "Running List Test..."
	$(PART3_TARGET) < $(LIST_TEST)

# Valgrind with vector test
valgrind_vector: $(PART3_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all $(PART3_TARGET) < $(VECTOR_TEST)

# Valgrind with list test
valgrind_list: $(PART3_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all $(PART3_TARGET) < $(LIST_TEST)

clean:
	rm -f $(PART3_TARGET) *.o
