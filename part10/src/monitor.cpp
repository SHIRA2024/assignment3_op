#include "core/State.hpp"
#include <pthread.h>
#include <unistd.h>
#include <iostream>

extern State sharedState;
extern pthread_mutex_t stateMutex;
extern pthread_cond_t chCond;
extern bool aboveThreshold;

void* monitorCH(void*) {
    while (true) {
        pthread_mutex_lock(&stateMutex);
        while ((sharedState.getCHSize() < 100 && !aboveThreshold) ||
               (sharedState.getCHSize() >= 100 && aboveThreshold)) {
            pthread_cond_wait(&chCond, &stateMutex);
        }
        if (sharedState.getCHSize() >= 100 && !aboveThreshold) {
            std::cout << "At Least 100 units belongs to CH\n";
            aboveThreshold = true;
        } else if (sharedState.getCHSize() < 100 && aboveThreshold) {
            std::cout << "At Least 100 units no longer belongs to CH\n";
            aboveThreshold = false;
        }
        pthread_mutex_unlock(&stateMutex);
        usleep(100000);
    }
    return nullptr;
}
