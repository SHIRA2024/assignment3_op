# Makefile for Part 7 – Threaded Convex Hull TCP Server

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude -pthread -Wno-array-bounds -Wno-stringop-overflow

SRC = src/server_part7.cpp src/core/State.cpp src/geom/Hull.cpp
BIN = ../ch_part7
VECTOR_TEST_FILE = ../test_part7_vector.txt
LIST_TEST_FILE = ../test_part7_list.txt

.PHONY: all clean run test test_vector test_list valgrind

all: $(BIN)

$(BIN): $(SRC)
	@echo "Building Part 7..."
	@$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Build complete: $@"

run_server: $(BIN)
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
run: test_vector test_list
	@echo "Finished running both vector and list tests."
