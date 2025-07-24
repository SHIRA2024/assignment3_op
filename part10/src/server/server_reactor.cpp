#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <vector>
#include <cstring>
#include <poll.h>
#include <pthread.h>
#include <sstream>
#include "../include/core/State.hpp"

enum Impl { VECTOR, LIST };

#define PORT 9035
#define BUFFER_SIZE 1024

extern State sharedState;
extern pthread_mutex_t stateMutex;
extern pthread_cond_t chCond;
extern bool aboveThreshold;

std::string processCommand(const std::string &line, State &state, bool &implChosen, Impl &currentImpl);

extern void* monitorCH(void*);

/**
 * @brief Main entry point for the server using the Reactor pattern.
 *        Accepts multiple client connections and uses poll to monitor
 *        their activity. Each command from a client is parsed and processed.
 *
 * @return int Exit status (0 if successful).
 */
int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    int yes = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 10);

    std::vector<pollfd> clients;
    clients.push_back({serverSocket, POLLIN, 0});

    pthread_t monitorThread;
    pthread_create(&monitorThread, nullptr, monitorCH, nullptr);

    std::vector<Impl> impls(1024, VECTOR);
    std::vector<bool> chosen(1024, false);

    char buf[BUFFER_SIZE];

    while (true) {
        poll(clients.data(), clients.size(), -1);

        for (size_t i = 0; i < clients.size(); ++i) {
            if (clients[i].revents & POLLIN) {

                // Handle new client connection
                if (clients[i].fd == serverSocket) {
                    sockaddr_in clientAddr{};
                    socklen_t addrSize = sizeof(clientAddr);
                    int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &addrSize);
                    fcntl(clientSocket, F_SETFL, O_NONBLOCK);
                    clients.push_back({clientSocket, POLLIN, 0});
                    std::cout << "New client connected from " << inet_ntoa(clientAddr.sin_addr) << "\n";
                } 
                // Handle client message
                else {
                    int clientSocket = clients[i].fd;
                    int bytesReceived = recv(clientSocket, buf, sizeof(buf) - 1, 0);

                    // Client disconnected or error
                    if (bytesReceived <= 0) {
                        close(clientSocket);
                        clients.erase(clients.begin() + i);
                        impls[clientSocket] = VECTOR;
                        chosen[clientSocket] = false;
                        --i;
                    } 
                    // Process client message
                    else {
                        buf[bytesReceived] = '\0';
                        std::istringstream iss(buf);
                        std::string line;

                        while (std::getline(iss, line)) {
                            if (!line.empty()) {
                                bool chosenVal = chosen[clientSocket];
                                std::string response = processCommand(line, sharedState, chosenVal, impls[clientSocket]);
                                chosen[clientSocket] = chosenVal;

                                if (response == "quit") {
                                    close(clientSocket);
                                    clients.erase(clients.begin() + i);
                                    impls[clientSocket] = VECTOR;
                                    chosen[clientSocket] = false;
                                    --i;
                                    break;
                                }

                                send(clientSocket, response.c_str(), response.length(), 0);
                            }
                        }
                    }
                }
            }
        }
    }

    close(serverSocket);
    return 0;
}
