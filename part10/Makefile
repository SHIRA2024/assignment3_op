CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
LDFLAGS = -pthread

SRC = src/core/State.cpp src/geom/Hull.cpp src/proactor/proactor.cpp \
      src/reactor/reactor.cpp src/globals.cpp src/commands.cpp src/monitor.cpp

VECTOR_TEST = test_vector.txt
LIST_TEST   = test_list.txt

.PHONY: all clean test_vector test_list run

all: server_reactor server_proactor

server_reactor: $(SRC) src/server/server_reactor.cpp src/main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

server_proactor: $(SRC) src/server/server_proactor.cpp src/main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

test_vector: server_reactor
	@echo "Stopping any previous server instance..."
	@pkill -x server_reactor > /dev/null 2>&1 || true
	@fuser -k 9035/tcp > /dev/null 2>&1 || true
	@echo "Starting server in background..."
	@./server_reactor > output_vector.txt 2>&1 & \
	SERVER_PID=$$!; \
	sleep 1; \
	echo "Sending vector commands:"; \
	nc localhost 9035 < $(VECTOR_TEST); \
	sleep 1; \
	if kill -0 $$SERVER_PID 2>/dev/null; then \
		echo "Stopping server..."; \
		kill $$SERVER_PID; \
	fi

test_list: server_reactor
	@echo "Stopping any previous server instance..."
	@pkill -x server_reactor > /dev/null 2>&1 || true
	@fuser -k 9035/tcp > /dev/null 2>&1 || true
	@echo "Starting server in background..."
	@./server_reactor > output_list.txt 2>&1 & \
	SERVER_PID=$$!; \
	sleep 1; \
	echo "Sending list commands:"; \
	nc localhost 9035 < $(LIST_TEST); \
	sleep 1; \
	if kill -0 $$SERVER_PID 2>/dev/null; then \
		echo "Stopping server..."; \
		kill $$SERVER_PID; \
	fi

run: test_vector test_list

clean:
	rm -f server_reactor server_proactor output_vector.txt output_list.txt
