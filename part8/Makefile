# Makefile for Part 8 – Proactor Library

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

SRC = src/proactor/proactor.cpp
OBJ = proactor.o
TARGET = libproactor_test.out

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	@echo "Compiling Proactor module..."
	$(CXX) $(CXXFLAGS) -c $(SRC) -o $(OBJ)
	@echo "Build successful: $(OBJ)"

clean:
	rm -f $(OBJ) $(TARGET)
	@echo "Cleaned build files."
