#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "core/State.hpp"
#include "geom/Hull.hpp"
#include "reactor/reactor.hpp"

#define PORT 9034
#define BUFFER_SIZE 1024

enum Impl { VECTOR, LIST };

State state;
Impl currentImpl = VECTOR;
bool implChosen = false;

/**
 * @brief Processes a single command from the client and returns a response string.
 */
std::string processCommand(const std::string &line) {
    std::istringstream iss(line);
    std::string cmd;
    iss >> cmd;

    if (cmd == "quit") {
        return "quit";
    }

    if (!implChosen) {
        if (cmd == "vector") {
            currentImpl = VECTOR;
            implChosen = true;
            return "Using vector implementation.\n";
        } else if (cmd == "list") {
            currentImpl = LIST;
            implChosen = true;
            return "Using list implementation.\n";
        } else {
            return "Please choose 'vector' or 'list' first.\n";
        }
    }

    if (cmd == "Newgraph") {
        int n;
        iss >> n;
        if (currentImpl == VECTOR)
            state.newGraphVector(n);
        else
            state.newGraphList(n);
        return "New graph created with capacity " + std::to_string(n) + ".\n";
    } else if (cmd == "Newpoint") {
        double x, y;
        iss >> x >> y;
        if (currentImpl == VECTOR)
            state.addPointVector(x, y);
        else
            state.addPointList(x, y);
        return "Added point (" + std::to_string(x) + ", " + std::to_string(y) + ").\n";
    } else if (cmd == "Removepoint") {
        double x, y;
        iss >> x >> y;
        if (currentImpl == VECTOR)
            state.removePointVector(x, y);
        else
            state.removePointList(x, y);
        return "Removed point (" + std::to_string(x) + ", " + std::to_string(y) + ").\n";
    } else if (cmd == "CH") {
        if (currentImpl == VECTOR)
            return state.computeCHVector();
        else
            return state.computeCHList();
    } else {
        return "Unknown command: " + cmd + "\n";
    }
}

/**
 * @brief Handles incoming data on the client socket.
 */
void handleClient(int client_fd) {
    char buffer[BUFFER_SIZE];
    int nbytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

    if (nbytes <= 0) {
        if (nbytes == 0) {
            std::cout << "Client disconnected on socket " << client_fd << "\n";
        } else {
            perror("recv");
        }
        close(client_fd);
        return;
    }

    buffer[nbytes] = '\0';
    std::istringstream iss(buffer);
    std::string line;
    while (std::getline(iss, line)) {
        if (!line.empty()) {
            std::string response = processCommand(line);
            if (response == "quit") {
                close(client_fd);
                return;
            }
            send(client_fd, response.c_str(), response.size(), 0);
        }
    }
}

/**
 * @brief Main function for Part 5 server.
 */
int main() {
    int listener;
    struct sockaddr_in serverAddr{};

    // Create socket
    if ((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return 1;
    }

    int yes = 1;
    if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(listener, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("bind");
        return 1;
    }

    if (listen(listener, 10) == -1) {
        perror("listen");
        return 1;
    }

    std::cout << "Server running on port " << PORT << "...\n";

    Reactor reactor;
    reactor.addHandler(listener, [&](int fd) {
        struct sockaddr_in clientAddr{};
        socklen_t addrlen = sizeof(clientAddr);
        int client_fd = accept(fd, (struct sockaddr *)&clientAddr, &addrlen);
        if (client_fd == -1) {
            perror("accept");
            return;
        }
        std::cout << "New connection from " << inet_ntoa(clientAddr.sin_addr)
                  << " on socket " << client_fd << "\n";
        reactor.addHandler(client_fd, handleClient);
    });

    reactor.run();
    return 0;
}
