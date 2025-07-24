#include "core/State.hpp"
#include "geom/Hull.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>

void State::newGraphVector(int n) {
    points.clear();
    points.reserve(n);
    std::cerr << "Vector: New graph created with capacity " << n << "\n";
}

void State::addPointVector(double x, double y) {
    points.push_back({x, y});
    std::cerr << "Vector: Added point (" << x << ", " << y << ")\n";
}

void State::removePointVector(double x, double y) {
    auto it = std::remove_if(points.begin(), points.end(),
        [&](const Pt &p) { return p.x == x && p.y == y; });
    if (it != points.end()) {
        points.erase(it, points.end());
        std::cerr << "Vector: Removed point (" << x << ", " << y << ")\n";
    } else {
        std::cerr << "Vector: Point (" << x << ", " << y << ") not found.\n";
    }
}

std::string State::computeCHVector() const {
    std::ostringstream out;
    if (points.size() < 3) {
        out << "0.000000\n";
        return out.str();
    }
    std::vector<Pt> temp = points;
    auto hull = buildHull(temp);
    double area = polygonArea(hull);

    out << "Hull points:\n";
    for (auto &p : hull) {
        out << "(" << p.x << ", " << p.y << ")\n";
    }
    out << area << "\n";
    return out.str();
}

// ------------------- List Implementation -------------------

void State::newGraphList(int n) {
    pointsList.clear();
    std::cerr << "List: New graph created with capacity " << n << "\n";
}

void State::addPointList(double x, double y) {
    pointsList.push_back({x, y});
    std::cerr << "List: Added point (" << x << ", " << y << ")\n";
}

void State::removePointList(double x, double y) {
    auto it = std::find_if(pointsList.begin(), pointsList.end(),
        [&](const Pt &p) { return p.x == x && p.y == y; });
    if (it != pointsList.end()) {
        pointsList.erase(it);
        std::cerr << "List: Removed point (" << x << ", " << y << ")\n";
    } else {
        std::cerr << "List: Point (" << x << ", " << y << ") not found.\n";
    }
}

std::string State::computeCHList() const {
    std::ostringstream out;
    if (pointsList.size() < 3) {
        out << "0.000000\n";
        return out.str();
    }
    std::vector<Pt> temp(pointsList.begin(), pointsList.end());
    auto hull = buildHull(temp);
    double area = polygonArea(hull);

    out << "Hull points:\n";
    for (auto &p : hull) {
        out << "(" << p.x << ", " << p.y << ")\n";
    }
    out << area << "\n";
    return out.str();
}
