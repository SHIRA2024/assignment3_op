# Makefile for Part 4 – Convex Hull TCP Server

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude -Wno-array-bounds -Wno-stringop-overflow

SRC = src/server_part4.cpp src/core/State.cpp src/geom/Hull.cpp
BIN = ../ch_part4
VECTOR_TEST_FILE = ../test_part4_vector.txt
LIST_TEST_FILE = ../test_part4_list.txt

.PHONY: all clean run test test_vector test_list valgrind

all: $(BIN)

$(BIN): $(SRC)
	@echo "Building Part 4..."
	@$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Build complete: $@"

run: $(BIN)
	@echo "Starting server..."
	@./$(BIN)

test_vector: $(BIN)
	@echo "Stopping old server (if any)..."
	@fuser -k 9034/tcp > /dev/null 2>&1 || true
	@echo "Starting server for vector test..."
	@./$(BIN) > /dev/null 2>&1 &
	@SERVER_PID=$$!; \
	sleep 1; \
	if [ -f $(VECTOR_TEST_FILE) ]; then \
		nc localhost 9034 < $(VECTOR_TEST_FILE); \
	else \
		echo "Error: $(VECTOR_TEST_FILE) not found!"; \
	fi; \
	kill $$SERVER_PID > /dev/null 2>&1 || true

test_list: $(BIN)
	@echo "Stopping old server (if any)..."
	@fuser -k 9034/tcp > /dev/null 2>&1 || true
	@echo "Starting server for list test..."
	@./$(BIN) > /dev/null 2>&1 &
	@SERVER_PID=$$!; \
	sleep 1; \
	if [ -f $(LIST_TEST_FILE) ]; then \
		nc localhost 9034 < $(LIST_TEST_FILE); \
	else \
		echo "Error: $(LIST_TEST_FILE) not found!"; \
	fi; \
	kill $$SERVER_PID > /dev/null 2>&1 || true

valgrind: $(BIN)
	@valgrind ./$(BIN)

clean:
	@rm -f $(BIN)
	@echo "Cleaned build files."
