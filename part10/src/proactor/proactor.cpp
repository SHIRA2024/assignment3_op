#include "../../include/proactor/proactor.hpp"
#include <pthread.h>
#include <unistd.h>
#include <stdexcept>

struct ProactorArgs {
    void* arg;
    proactorFunc func;
};

void* proactorThreadEntry(void* rawArgs) {
    ProactorArgs* args = static_cast<ProactorArgs*>(rawArgs);
    void* result = args->func(args->arg);
    delete args;
    return result;
}

pthread_t startProactor(void* arg, proactorFunc threadFunc) {
    pthread_t tid;
    ProactorArgs* args = new ProactorArgs{arg, threadFunc};
    if (pthread_create(&tid, nullptr, proactorThreadEntry, args) != 0) {
        delete args;
        throw std::runtime_error("Failed to create proactor thread");
    }
    return tid;
}

int stopProactor(pthread_t tid) {
    return pthread_cancel(tid);
}
