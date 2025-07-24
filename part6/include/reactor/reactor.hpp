#pragma once

#include <sys/epoll.h>
#include <functional>
#include <unordered_map>

/**
 * @brief A simple Reactor pattern using epoll.
 *        Allows registering file descriptors (sockets) with callbacks for read events.
 */
class Reactor {
public:
    Reactor();
    ~Reactor();

    /**
     * @brief Adds a file descriptor to be monitored for read events.
     * @param fd File descriptor.
     * @param callback Function to call when fd is readable.
     */
    void addHandler(int fd, const std::function<void(int)> &callback);

    /**
     * @brief Removes a file descriptor from the reactor.
     * @param fd File descriptor to remove.
     */
    void removeHandler(int fd);

    /**
     * @brief Starts the event loop (blocking).
     */
    void run();

    /**
     * @brief Stops the reactor loop.
     */
    void stop();

private:
    int epoll_fd;
    bool running;
    std::unordered_map<int, std::function<void(int)>> handlers;
};
