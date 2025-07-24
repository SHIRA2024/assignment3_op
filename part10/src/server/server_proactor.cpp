#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <vector>
#include <cstring>
#include <future>
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
 * @brief Handles communication with a single client using a dedicated thread.
 *        Receives and processes commands, and sends back responses.
 * 
 * @param clientSocket The socket connected to the client.
 * @param chosen Reference to a vector indicating if the implementation was selected.
 * @param impls Reference to a vector storing the implementation type per client.
 */
void handleClient(int clientSocket, std::vector<bool>& chosen, std::vector<Impl>& impls) {
    char buf[BUFFER_SIZE];
    int bytesReceived = recv(clientSocket, buf, sizeof(buf) - 1, 0);
    if (bytesReceived <= 0) {
        close(clientSocket);
        return;
    }

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
                return;
            }

            send(clientSocket, response.c_str(), response.length(), 0);
        }
    }
}

/**
 * @brief Main entry point for the proactor server.
 *        Sets up the listening socket, launches the monitor thread,
 *        and accepts incoming client connections. Each client is handled
 *        using a dedicated asynchronous task via std::async.
 * 
 * @return int Exit code (0 for success).
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

    pthread_t monitorThread;
    pthread_create(&monitorThread, nullptr, monitorCH, nullptr);

    std::vector<Impl> impls(1024, VECTOR);
    std::vector<bool> chosen(1024, false);

    while (true) {
        sockaddr_in clientAddr{};
        socklen_t addrSize = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &addrSize);
        if (clientSocket < 0) continue;

        fcntl(clientSocket, F_SETFL, O_NONBLOCK);
        std::cout << "New client connected from " << inet_ntoa(clientAddr.sin_addr) << "\n";

        auto fut = std::async(std::launch::async, handleClient, clientSocket, std::ref(chosen), std::ref(impls));
    }

    close(serverSocket);
    return 0;
}
