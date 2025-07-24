# Makefile for Part 5 – Reactor-based Convex Hull Server

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

# Directories
SRC_DIR = src
BIN_DIR = ..
PART5_TARGET = $(BIN_DIR)/ch_part5

# Test files
VECTOR_TEST = ../test_part5_vector.txt
LIST_TEST   = ../test_part5_list.txt

# Sources
PART5_SRCS = $(SRC_DIR)/server_part5.cpp \
             $(SRC_DIR)/core/State.cpp \
             $(SRC_DIR)/geom/Hull.cpp \
             $(SRC_DIR)/reactor/reactor.cpp

.PHONY: all clean test_vector test_list run

all: $(PART5_TARGET)

$(PART5_TARGET): $(PART5_SRCS)
	@echo "Building Part 5..."
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Build complete: $(PART5_TARGET)"

# Test with vector implementation
test_vector: $(PART5_TARGET)
	@echo "Stopping any previous server instance..."
	@pkill -x ch_part5 > /dev/null 2>&1 || true
	@fuser -k 9034/tcp > /dev/null 2>&1 || true
	@echo "Starting server in background..."
	@./../ch_part5 > /dev/null 2>&1 &
	@SERVER_PID=$$!; \
	sleep 1; \
	if [ -f $(VECTOR_TEST) ]; then \
		nc localhost 9034 < $(VECTOR_TEST); \
	else \
		echo "Error: $(VECTOR_TEST) not found!"; \
	fi; \
	if kill -0 $$SERVER_PID 2>/dev/null; then \
		kill $$SERVER_PID || true; \
	fi

# Test with list implementation
test_list: $(PART5_TARGET)
	@echo "Stopping any previous server instance..."
	@pkill -x ch_part5 > /dev/null 2>&1 || true
	@fuser -k 9034/tcp > /dev/null 2>&1 || true
	@echo "Starting server in background..."
	@./../ch_part5 > /dev/null 2>&1 &
	@SERVER_PID=$$!; \
	sleep 1; \
	if [ -f $(LIST_TEST) ]; then \
		nc localhost 9034 < $(LIST_TEST); \
	else \
		echo "Error: $(LIST_TEST) not found!"; \
	fi; \
	if kill -0 $$SERVER_PID 2>/dev/null; then \
		kill $$SERVER_PID || true; \
	fi

# Run both tests in sequence
run: test_vector test_list

clean:
	rm -f $(PART5_TARGET)