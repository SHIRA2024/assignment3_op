#include "core/State.hpp"
#include <pthread.h>

State sharedState;
pthread_mutex_t stateMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t chCond = PTHREAD_COND_INITIALIZER;
bool aboveThreshold = false;
