#include "../../include/proactor/proactor.hpp"
#include <pthread.h>
#include <unistd.h>
#include <stdexcept>

/**
 * @brief Struct to encapsulate arguments for the proactor thread.
 *        Contains the function pointer and its corresponding argument.
 */
struct ProactorArgs {
    void* arg;             ///< Argument to be passed to the function
    proactorFunc func;     ///< Function pointer to execute in the thread
};

/**
 * @brief Entry point function for the proactor thread.
 *        Executes the provided function with the given argument.
 * 
 * @param rawArgs Pointer to ProactorArgs containing function and argument.
 * @return void* The result returned by the function, if any.
 */
void* proactorThreadEntry(void* rawArgs) {
    ProactorArgs* args = static_cast<ProactorArgs*>(rawArgs);
    void* result = args->func(args->arg);
    delete args;
    return result;
}

/**
 * @brief Starts a new thread to run a given function asynchronously (proactor-style).
 * 
 * @param arg Argument to pass to the thread function.
 * @param threadFunc Function pointer to run inside the thread.
 * @return pthread_t Thread ID of the newly created thread.
 * @throws std::runtime_error If thread creation fails.
 */
pthread_t startProactor(void* arg, proactorFunc threadFunc) {
    pthread_t tid;
    ProactorArgs* args = new ProactorArgs{arg, threadFunc};
    if (pthread_create(&tid, nullptr, proactorThreadEntry, args) != 0) {
        delete args;
        throw std::runtime_error("Failed to create proactor thread");
    }
    return tid;
}

/**
 * @brief Stops a running proactor thread by sending a cancellation request.
 * 
 * @param tid Thread ID of the proactor thread to cancel.
 * @return int Return code from pthread_cancel.
 */
int stopProactor(pthread_t tid) {
    return pthread_cancel(tid);
}
