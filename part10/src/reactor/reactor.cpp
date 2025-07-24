#include "reactor/reactor.hpp"
#include <unistd.h>
#include <stdexcept>
#include <cstring>

/**
 * @brief Constructor for the Reactor class.
 * Creates an epoll instance that will monitor file descriptors for I/O events.
 * Throws a runtime_error if the epoll instance cannot be created.
 */
Reactor::Reactor() : running(false) {
    epoll_fd = epoll_create1(0); // Create an epoll file descriptor
    if (epoll_fd == -1) {
        throw std::runtime_error("Failed to create epoll instance: " + std::string(strerror(errno)));
    }
}

/**
 * @brief Destructor for the Reactor class.
 * Closes the epoll file descriptor to release resources.
 */
Reactor::~Reactor() {
    close(epoll_fd);
}

/**
 * @brief Registers a new file descriptor (fd) with the reactor and associates
 * a callback function that will be executed when the fd is ready for reading.
 * 
 * @param fd The file descriptor to monitor.
 * @param callback The function to call when the fd becomes ready.
 * 
 * @throws runtime_error if adding the fd to the epoll instance fails.
 */
void Reactor::addHandler(int fd, const std::function<void(int)> &callback) {
    epoll_event ev{};
    ev.events = EPOLLIN;        // Monitor read events
    ev.data.fd = fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev) == -1) {
        throw std::runtime_error("Failed to add fd to epoll: " + std::string(strerror(errno)));
    }
    handlers[fd] = callback;    // Store the callback function for this fd
}

/**
 * @brief Removes a previously registered file descriptor (fd) from the reactor.
 * @param fd The file descriptor to remove.
 */
void Reactor::removeHandler(int fd) {
    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, nullptr); // Remove fd from epoll monitoring
    handlers.erase(fd);                              // Erase callback associated with fd
}

/**
 * @brief Starts the event loop of the reactor.
 * Continuously waits for I/O events on registered file descriptors and
 * calls the appropriate callback function when an event occurs.
 * 
 * @throws runtime_error if epoll_wait fails (other than being interrupted).
 */
void Reactor::run() {
    running = true;
    epoll_event events[10];  // Array to store triggered events

    while (running) {
        // Wait indefinitely for events on any of the monitored file descriptors
        int n = epoll_wait(epoll_fd, events, 10, -1);
        if (n == -1) {
            if (errno == EINTR) continue;  // Interrupted by signal, just retry
            throw std::runtime_error("epoll_wait failed: " + std::string(strerror(errno)));
        }
        // Iterate over all ready events
        for (int i = 0; i < n; ++i) {
            int fd = events[i].data.fd;
            // If we have a handler for this fd, call it
            if (handlers.find(fd) != handlers.end()) {
                handlers[fd](fd);
            }
        }
    }
}

/**
 * @brief Stops the reactor's event loop.
 * Sets the running flag to false, causing the run() loop to exit.
 */
void Reactor::stop() {
    running = false;
}