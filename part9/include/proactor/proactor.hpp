#pragma once

#include <pthread.h>

/**
 * @brief A simple Proactor interface.
 *        Starts a thread to handle a connected socket using a provided handler function.
 */

// Updated function pointer type: takes void* argument (standard for pthreads)
typedef void* (*proactorFunc)(void*);

/**
 * @brief Starts a new thread running the given handler function on the socket.
 * @param sockfd The socket file descriptor for the client.
 * @param threadFunc The function to run in the new thread.
 * @return The pthread_t id of the created thread.
 */
pthread_t startProactor(void* arg, proactorFunc threadFunc);


/**
 * @brief Stops the given thread (best effort).
 * @param tid The thread id to cancel.
 * @return 0 on success, or error code.
 */
int stopProactor(pthread_t tid);
