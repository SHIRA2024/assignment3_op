#pragma once
#include <string>
#include "core/State.hpp"

enum Impl { VECTOR, LIST };

std::string processCommand(const std::string& line, State& state, bool& implChosen, Impl& currentImpl);
