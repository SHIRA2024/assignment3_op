#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../include/core/State.hpp"
#include "../include/geom/Hull.hpp"
#include <cstring>   // For memset

#define PORT 9034
#define BUFFER_SIZE 1024

// Implementation type: either VECTOR or LIST
enum Impl { VECTOR, LIST };

/**
 * @brief Processes a single command from the client.
 *        It delegates operations to the State object.
 * @param line        The command string (e.g., "Newpoint 1 1").
 * @param state       Reference to the current State object.
 * @param implChosen  Whether implementation (vector/list) has been chosen.
 * @param currentImpl The currently selected implementation type.
 * @return Response string to send back to the client.
 */
std::string processCommand(const std::string &line, State &state, bool &implChosen, Impl &currentImpl) {
    std::istringstream iss(line);
    std::string cmd;
    iss >> cmd;

    if (cmd == "quit") return "quit";

    if (!implChosen) {
        if (cmd == "vector") { currentImpl = VECTOR; implChosen = true; return "Using vector implementation.\n"; }
        else if (cmd == "list") { currentImpl = LIST; implChosen = true; return "Using list implementation.\n"; }
        else return "Please choose 'vector' or 'list' first.\n";
    }

    if (cmd == "Newgraph") {
        int n; iss >> n;
        (currentImpl == VECTOR) ? state.newGraphVector(n) : state.newGraphList(n);
        return "New graph created with capacity " + std::to_string(n) + ".\n";
    } else if (cmd == "Newpoint") {
        double x, y; iss >> x >> y;
        (currentImpl == VECTOR) ? state.addPointVector(x, y) : state.addPointList(x, y);
        return "Added point (" + std::to_string(x) + ", " + std::to_string(y) + ").\n";
    } else if (cmd == "Removepoint") {
        double x, y; iss >> x >> y;
        (currentImpl == VECTOR) ? state.removePointVector(x, y) : state.removePointList(x, y);
        return "Removed point (" + std::to_string(x) + ", " + std::to_string(y) + ").\n";
    } else if (cmd == "CH") {
        return (currentImpl == VECTOR) ? state.computeCHVector() : state.computeCHList();
    }

    return "Unknown command: " + cmd + "\n";
}

/**
 * @brief Main function that starts the TCP server.
 *        It waits for connections, reads commands, and sends responses.
 */
int main() {
    int listener, newfd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrlen;
    fd_set master, read_fds;
    int fdmax;
    char buf[BUFFER_SIZE];
    int nbytes;

    State state;
    Impl currentImpl = VECTOR;
    bool implChosen = false;

    // Create a TCP socket
    listener = socket(AF_INET, SOCK_STREAM, 0);
    int yes = 1;
    setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    // Bind the socket to port 9034
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);
    memset(&(serverAddr.sin_zero), '\0', 8);
    bind(listener, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    listen(listener, 10);

    // Prepare the file descriptor sets for select()
    FD_ZERO(&master);
    FD_ZERO(&read_fds);
    FD_SET(listener, &master);
    fdmax = listener;

    std::cout << "Server running on port " << PORT << "...\n";

    while (true) {
        read_fds = master;
        select(fdmax + 1, &read_fds, NULL, NULL, NULL);

        for (int i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) {
                if (i == listener) {
                    // Accept a new connection
                    addrlen = sizeof(clientAddr);
                    newfd = accept(listener, (struct sockaddr *)&clientAddr, &addrlen);
                    FD_SET(newfd, &master);
                    if (newfd > fdmax) fdmax = newfd;
                    std::cout << "New connection from " << inet_ntoa(clientAddr.sin_addr)
                              << " on socket " << newfd << "\n";
                } else {
                    // Handle incoming data from client
                    if ((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0) {
                        close(i);
                        FD_CLR(i, &master);
                    } else {
                        buf[nbytes] = '\0';
                        std::istringstream iss(buf);
                        std::string line;
                        while (std::getline(iss, line)) {
                            if (!line.empty()) {
                                std::string response = processCommand(line, state, implChosen, currentImpl);
                                if (response == "quit") {
                                    close(i);
                                    FD_CLR(i, &master);
                                    break;
                                }
                                send(i, response.c_str(), response.size(), 0);
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
