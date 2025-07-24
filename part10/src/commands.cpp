#include "../include/commands.hpp"
#include <sstream>
#include <iostream>

extern pthread_mutex_t stateMutex;
extern pthread_cond_t chCond;

std::string processCommand(const std::string& line, State& state, bool& implChosen, Impl& currentImpl) {
    std::istringstream iss(line);
    std::string cmd;
    iss >> cmd;

    pthread_mutex_lock(&stateMutex);

    if (cmd == "use") {
        std::string type;
        iss >> type;
        if (type == "vector") {
            currentImpl = VECTOR;
            implChosen = true;
            pthread_mutex_unlock(&stateMutex);
            return "Using vector implementation.\n";
        } else if (type == "list") {
            currentImpl = LIST;
            implChosen = true;
            pthread_mutex_unlock(&stateMutex);
            return "Using list implementation.\n";
        } else {
            pthread_mutex_unlock(&stateMutex);
            return "Invalid implementation type.\n";
        }
    }

    if (!implChosen) {
        pthread_mutex_unlock(&stateMutex);
        return "Please choose implementation first using 'use vector' or 'use list'.\n";
    }

    if (cmd == "new") {
        int n;
        iss >> n;
        if (currentImpl == VECTOR)
            state.newGraphVector(n);
        else
            state.newGraphList(n);
        pthread_mutex_unlock(&stateMutex);
        return "New graph created with capacity " + std::to_string(n) + ".\n";
    } else if (cmd == "add") {
        double x, y;
        iss >> x >> y;
        if (currentImpl == VECTOR)
            state.addPointVector(x, y);
        else
            state.addPointList(x, y);
        pthread_cond_signal(&chCond); // לעדכון המוניטור
        pthread_mutex_unlock(&stateMutex);
        return "Added point (" + std::to_string(x) + ", " + std::to_string(y) + ").\n";
    } else if (cmd == "remove") {
        double x, y;
        iss >> x >> y;
        if (currentImpl == VECTOR)
            state.removePointVector(x, y);
        else
            state.removePointList(x, y);
        pthread_cond_signal(&chCond);
        pthread_mutex_unlock(&stateMutex);
        return "Removed point (" + std::to_string(x) + ", " + std::to_string(y) + ").\n";
    } else if (cmd == "ch") {
        std::string result = (currentImpl == VECTOR) ? state.computeCHVector()
                                                     : state.computeCHList();
        pthread_cond_signal(&chCond);
        pthread_mutex_unlock(&stateMutex);
        return result;
    } else if (cmd == "quit") {
        pthread_mutex_unlock(&stateMutex);
        return "quit";
    }

    pthread_mutex_unlock(&stateMutex);
    return "Unknown command.\n";
}
