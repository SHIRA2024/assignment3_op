# Makefile for Part 2 – Dynamic Convex Hull with Profiling

CXX = g++ 
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra -O2

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = ..
PART2_TARGET = $(BIN_DIR)/ch_part2

# Test files (relative to part2)
VECTOR_TEST = ../test_part2_vector.txt
LIST_TEST   = ../test_part2_list.txt

# Source files
PART2_SRCS = $(SRC_DIR)/main.cpp \
             $(SRC_DIR)/core/State.cpp \
             $(SRC_DIR)/geom/Hull.cpp

.PHONY: all clean run run_vector run_list valgrind_vector valgrind_list

all: $(PART2_TARGET)

$(PART2_TARGET): $(PART2_SRCS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Run both vector and list tests
run: run_vector run_list

# Run with vector test input
run_vector: $(PART2_TARGET)
	@echo "Running Vector Test..."
	@$(PART2_TARGET) < $(VECTOR_TEST)

# Run with list test input
run_list: $(PART2_TARGET)
	@echo "Running List Test..."
	@$(PART2_TARGET) < $(LIST_TEST)

# Valgrind with vector test
valgrind_vector: $(PART2_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all $(PART2_TARGET) < $(VECTOR_TEST)

# Valgrind with list test
valgrind_list: $(PART2_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all $(PART2_TARGET) < $(LIST_TEST)

clean:
	rm -f $(PART2_TARGET) *.o
