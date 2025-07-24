
#include "core/State.hpp"
#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include "../include/core/monitor.hpp"


extern State sharedState;
extern pthread_mutex_t stateMutex;
extern pthread_cond_t chCond;
extern bool aboveThreshold;

