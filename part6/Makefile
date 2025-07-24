# Makefile for Part 6 – Multi-client Convex Hull Server (Based on Reactor)

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

SRC_DIR = src
BIN_DIR = ..
PART6_TARGET = $(BIN_DIR)/ch_part6

# Use test files from part 5
VECTOR_TEST = ../test_part5_vector.txt
LIST_TEST   = ../test_part5_list.txt

PART6_SRCS = $(SRC_DIR)/server_part6.cpp \
             $(SRC_DIR)/core/State.cpp \
             $(SRC_DIR)/geom/Hull.cpp \
             $(SRC_DIR)/reactor/reactor.cpp

.PHONY: all clean test_vector test_list run valgrind_vector valgrind_list

all: $(PART6_TARGET)

$(PART6_TARGET): $(PART6_SRCS)
	@echo "Building Part 6..."
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Build complete: $(PART6_TARGET)"

# Test with vector implementation
test_vector: $(PART6_TARGET)
	@echo "Stopping any previous server instance..."
	@pkill -x ch_part6 > /dev/null 2>&1 || true
	@fuser -k 9034/tcp > /dev/null 2>&1 || true
	@echo "Starting server in background..."
	@./../ch_part6 > /dev/null 2>&1 &
	@SERVER_PID=$$!; \
	sleep 1; \
	echo "Running vector test..."; \
	nc localhost 9034 < $(VECTOR_TEST); \
	if kill -0 $$SERVER_PID 2>/dev/null; then \
		kill $$SERVER_PID || true; \
	fi

# Test with list implementation
test_list: $(PART6_TARGET)
	@echo "Stopping any previous server instance..."
	@pkill -x ch_part6 > /dev/null 2>&1 || true
	@fuser -k 9034/tcp > /dev/null 2>&1 || true
	@echo "Starting server in background..."
	@./../ch_part6 > /dev/null 2>&1 &
	@SERVER_PID=$$!; \
	sleep 1; \
	echo "Running list test..."; \
	nc localhost 9034 < $(LIST_TEST); \
	if kill -0 $$SERVER_PID 2>/dev/null; then \
		kill $$SERVER_PID || true; \
	fi

# Run both tests
run: test_vector test_list

# Valgrind checks
valgrind_vector: $(PART6_TARGET)
	valgrind --leak-check=full ./../ch_part6 < $(VECTOR_TEST)

valgrind_list: $(PART6_TARGET)
	valgrind --leak-check=full ./../ch_part6 < $(LIST_TEST)

clean:
	rm -f $(PART6_TARGET)