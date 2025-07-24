#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "../include/core/State.hpp"
#include "../include/geom/Hull.hpp"
#include <cstring>

#define PORT 9034
#define BUFFER_SIZE 1024

enum Impl { VECTOR, LIST };


State sharedState;
pthread_mutex_t stateMutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * @brief Processes a single command from the client.
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

    pthread_mutex_lock(&stateMutex); 
    std::string response;
    if (cmd == "Newgraph") {
        int n; iss >> n;
        (currentImpl == VECTOR) ? state.newGraphVector(n) : state.newGraphList(n);
        response = "New graph created with capacity " + std::to_string(n) + ".\n";
    } else if (cmd == "Newpoint") {
        double x, y; iss >> x >> y;
        (currentImpl == VECTOR) ? state.addPointVector(x, y) : state.addPointList(x, y);
        response = "Added point (" + std::to_string(x) + ", " + std::to_string(y) + ").\n";
    } else if (cmd == "Removepoint") {
        double x, y; iss >> x >> y;
        (currentImpl == VECTOR) ? state.removePointVector(x, y) : state.removePointList(x, y);
        response = "Removed point (" + std::to_string(x) + ", " + std::to_string(y) + ").\n";
    } else if (cmd == "CH") {
        response = (currentImpl == VECTOR) ? state.computeCHVector() : state.computeCHList();
    } else {
        response = "Unknown command: " + cmd + "\n";
    }
    pthread_mutex_unlock(&stateMutex); 
    return response;
}

/**
 * @brief Thread function that handles a single client.
 */
void* handleClient(void* arg) {
    int clientSocket = *(int*)arg;
    delete (int*)arg; // Clean up dynamically allocated memory

    char buf[BUFFER_SIZE];
    Impl currentImpl = VECTOR;
    bool implChosen = false;

    while (true) {
        int bytesReceived = recv(clientSocket, buf, sizeof(buf) - 1, 0);
        if (bytesReceived <= 0) break;

        buf[bytesReceived] = '\0';
        std::istringstream iss(buf);
        std::string line;

        while (std::getline(iss, line)) {
            if (!line.empty()) {
                std::string response = processCommand(line, sharedState, implChosen, currentImpl);
                if (response == "quit") {
                    close(clientSocket);
                    return nullptr;
                }
                send(clientSocket, response.c_str(), response.length(), 0);
            }
        }
    }

    close(clientSocket);
    return nullptr;
}

/**
 * @brief Main function that starts the multi-threaded server.
 */
int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    int yes = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);
    memset(&(serverAddr.sin_zero), '\0', 8);

    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 10);

    std::cout << "Threaded server running on port " << PORT << "...\n";

    while (true) {
        struct sockaddr_in clientAddr;
        socklen_t addrSize = sizeof(clientAddr);
        int* clientSocket = new int;
        *clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrSize);
        std::cout << "New client connected from " << inet_ntoa(clientAddr.sin_addr) << "\n";

        pthread_t tid;
        pthread_create(&tid, nullptr, handleClient, clientSocket);
        pthread_detach(tid); 
    }

    close(serverSocket);
    return 0;
}
