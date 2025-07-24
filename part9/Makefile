# Makefile for Part 9 – Proactor-based Convex Hull Server

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

# Directories
SRC_DIR = src
BIN_DIR = ..
TARGET = $(BIN_DIR)/ch_part9

# Test files
VECTOR_TEST = ../test_part9_vector.txt
LIST_TEST   = ../test_part9_list.txt

# Sources (adjusted path to server_part9.cpp)
SRCS = $(SRC_DIR)/proactor/server_part9.cpp \
       $(SRC_DIR)/core/State.cpp \
       $(SRC_DIR)/geom/Hull.cpp \
       $(SRC_DIR)/proactor/proactor.cpp

.PHONY: all clean test_vector test_list run

all: $(TARGET)

$(TARGET): $(SRCS)
	@echo "Building Part 9..."
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Build complete: $(TARGET)"

test_vector: $(TARGET)
	@echo "Stopping old server (if any)..."
	@fuser -k 9034/tcp > /dev/null 2>&1 || true
	@echo "Starting server for vector test..."
	@$(TARGET) > /dev/null 2>&1 &
	@sleep 1
	@if [ -f $(VECTOR_TEST) ]; then \
		nc localhost 9034 < $(VECTOR_TEST); \
	else \
		echo "Error: $(VECTOR_TEST) not found!"; \
	fi

test_list: $(TARGET)
	@echo "Stopping old server (if any)..."
	@fuser -k 9034/tcp > /dev/null 2>&1 || true
	@echo "Starting server for list test..."
	@$(TARGET) > /dev/null 2>&1 &
	@sleep 1
	@if [ -f $(LIST_TEST) ]; then \
		nc localhost 9034 < $(LIST_TEST); \
	else \
		echo "Error: $(LIST_TEST) not found!"; \
	fi

run: test_vector test_list

clean:
	rm -f $(TARGET)
	@echo "Cleaned build files."
