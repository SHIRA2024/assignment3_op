#include <iostream>
#include <string>
#include "../include/core/State.hpp"

/**
 * @brief Part 3 main.
 * Reads commands from stdin and applies them to vector or list implementation.
 */
int main() {
    State state;
    std::string cmd;
    enum Impl { VECTOR, LIST } currentImpl = VECTOR;

    // Choose implementation
    std::string impl;
    if (!(std::cin >> impl)) return 0;
    if (impl == "list") currentImpl = LIST;
    else currentImpl = VECTOR;

    // Command loop
    while (std::cin >> cmd) {
        if (cmd == "Newgraph") {
            int n;
            std::cin >> n;
            if (currentImpl == VECTOR) state.newGraphVector(n);
            else state.newGraphList(n);
        }
        else if (cmd == "Newpoint") {
            double x, y;
            std::cin >> x >> y;
            if (currentImpl == VECTOR) state.addPointVector(x, y);
            else state.addPointList(x, y);
        }
        else if (cmd == "Removepoint") {
            double x, y;
            std::cin >> x >> y;
            if (currentImpl == VECTOR) state.removePointVector(x, y);
            else state.removePointList(x, y);
        }
        else if (cmd == "CH") {
            if (currentImpl == VECTOR)
                std::cout << state.computeCHVector();
            else
                std::cout << state.computeCHList();
        }
        else {
            std::cerr << "Unknown command: " << cmd << "\n";
        }
    }
    return 0;
}
