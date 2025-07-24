#include "core/State.hpp"
#include "reactor/reactor.hpp"
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <sstream>

#define PORT 9034
#define BUFFER_SIZE 1024

// Enum to select which implementation to use: vector or list
enum Impl { VECTOR, LIST };

// Global state and reactor
State state;
Reactor reactor;
Impl currentImpl = VECTOR;  // Default implementation is vector

/**
 * @brief Processes a single command and returns the server's response.
 * 
 * @param line A command line received from the client.
 * @return std::string The response to be sent back to the client.
 */
std::string processCommand(const std::string &line) {
    std::istringstream iss(line);
    std::string cmd;
    iss >> cmd;

    if (cmd == "vector") {
        currentImpl = VECTOR;
        return "Using vector implementation.\n";
    } else if (cmd == "list") {
        currentImpl = LIST;
        return "Using list implementation.\n";
    } else if (cmd == "Newgraph") {
        int n;
        iss >> n;
        if (currentImpl == VECTOR) state.newGraphVector(n);
        else state.newGraphList(n);
        return "New graph created with capacity " + std::to_string(n) + ".\n";
    } else if (cmd == "Newpoint") {
        double x, y;
        iss >> x >> y;
        if (currentImpl == VECTOR) state.addPointVector(x, y);
        else state.addPointList(x, y);
        return "Added point (" + std::to_string(x) + ", " + std::to_string(y) + ").\n";
    } else if (cmd == "Removepoint") {
        double x, y;
        iss >> x >> y;
        if (currentImpl == VECTOR) state.removePointVector(x, y);
        else state.removePointList(x, y);
        return "Removed point (" + std::to_string(x) + ", " + std::to_string(y) + ").\n";
    } else if (cmd == "CH") {
        return (currentImpl == VECTOR) ? state.computeCHVector() : state.computeCHList();
    } else if (cmd == "quit") {
        reactor.stop();
        return "Server shutting down...\n";
    }

    return "Unknown command: " + cmd + "\n";
}

/**
 * @brief Handles client requests (callback for Reactor).
 *        Reads all lines from the client and processes each command.
 *
 * @param client_fd The client's socket file descriptor.
 */
void handleClient(int client_fd) {
    char buffer[BUFFER_SIZE];
    int bytesRead = read(client_fd, buffer, BUFFER_SIZE - 1);
    if (bytesRead <= 0) {
        close(client_fd);
        reactor.removeHandler(client_fd);
        return;
    }
    buffer[bytesRead] = '\0';

    // Process all commands in the buffer
    std::istringstream input(buffer);
    std::string line;
    while (std::getline(input, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back(); // Handle CRLF
        std::string response = processCommand(line);
        if (!response.empty()) {
            ssize_t written = write(client_fd, response.c_str(), response.size());
            (void)written; // Avoid unused-result warning
        }
    }
}

/**
 * @brief Accepts new clients (callback for Reactor).
 * 
 * @param server_fd The server socket file descriptor.
 */
void acceptClient(int server_fd) {
    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (sockaddr*)&client_addr, &client_len);
    if (client_fd >= 0) {
        reactor.addHandler(client_fd, handleClient);
    }
}

/**
 * @brief Main server entry point.
 */
int main() {
    // Create server socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        return 1;
    }

    // Allow quick socket reuse
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Bind server to port
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_fd);
        return 1;
    }

    // Start listening
    if (listen(server_fd, 10) < 0) {
        perror("listen");
        close(server_fd);
        return 1;
    }

    std::cout << "Server running on port " << PORT << "...\n";

    // Add server_fd to Reactor for handling new clients
    reactor.addHandler(server_fd, acceptClient);

    // Start the Reactor event loop
    reactor.run();

    close(server_fd);
    return 0;
}