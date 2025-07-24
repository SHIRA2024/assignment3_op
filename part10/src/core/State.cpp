#include "../../include/core/State.hpp"
#include "geom/Hull.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std::chrono;

/**
 * @brief Initializes a new graph (vector implementation).
 *        Clears existing points and reserves space for `n` points.
 */
void State::newGraphVector(int n) {
    points.clear();
    points.reserve(n);
    std::cerr << "Vector: New graph created with capacity " << n << "\n";
}

/**
 * @brief Adds a point to the vector-based graph.
 *        Measures and logs the execution time.
 */
void State::addPointVector(double x, double y) {
    auto start = high_resolution_clock::now();
    points.push_back({x, y});
    auto end = high_resolution_clock::now();
    std::cerr << "Vector: addPoint took " 
              << duration_cast<microseconds>(end - start).count() << " us\n";
}

/**
 * @brief Removes a point (x, y) from the vector-based graph if it exists.
 */
void State::removePointVector(double x, double y) {
    auto start = high_resolution_clock::now();
    auto it = std::remove_if(points.begin(), points.end(),
        [&](const Pt &p) { return p.x == x && p.y == y; });
    if (it != points.end()) {
        points.erase(it, points.end());
        std::cerr << "Vector: Removed point (" << x << ", " << y << ")\n";
    }
    auto end = high_resolution_clock::now();
    std::cerr << "Vector: removePoint took " 
              << duration_cast<microseconds>(end - start).count() << " us\n";
}

/**
 * @brief Computes the convex hull of points (vector implementation) and returns
 *        a formatted string containing hull points and area.
 */
std::string State::computeCHVector() const {
    std::ostringstream out;
    if (points.size() < 3) {
        out << "0.000000\n";
        return out.str();
    }
    auto start = high_resolution_clock::now();
    std::vector<Pt> temp = points; // Make a copy since buildHull modifies input.
    auto hull = buildHull(temp);
    double area = polygonArea(hull);
    auto end = high_resolution_clock::now();

    out << "Hull points:\n";
    for (auto &p : hull)
        out << "(" << p.x << ", " << p.y << ")\n";
    out << area << "\n";

    std::cerr << "Vector: computeCH took "
              << duration_cast<microseconds>(end - start).count() << " us\n";
    return out.str();
}

// -------------------------------------------------------------------
// List-based implementation of the same functionality as above.
// -------------------------------------------------------------------

/**
 * @brief Initializes a new graph (list implementation).
 */
void State::newGraphList(int n) {
    pointsList.clear();
    std::cerr << "List: New graph created with capacity " << n << "\n";
}

/**
 * @brief Adds a point to the list-based graph.
 */
void State::addPointList(double x, double y) {
    auto start = high_resolution_clock::now();
    pointsList.push_back({x, y});
    auto end = high_resolution_clock::now();
    std::cerr << "List: addPoint took "
              << duration_cast<microseconds>(end - start).count() << " us\n";
}

/**
 * @brief Removes a point (x, y) from the list-based graph if it exists.
 */
void State::removePointList(double x, double y) {
    auto start = high_resolution_clock::now();
    auto it = std::find_if(pointsList.begin(), pointsList.end(),
        [&](const Pt &p) { return p.x == x && p.y == y; });
    if (it != pointsList.end()) {
        pointsList.erase(it);
        std::cerr << "List: Removed point (" << x << ", " << y << ")\n";
    }
    auto end = high_resolution_clock::now();
    std::cerr << "List: removePoint took "
              << duration_cast<microseconds>(end - start).count() << " us\n";
}


int State::getCHSize() const {
    if (!points.empty()) {
        std::vector<Pt> temp = points;
        return buildHull(temp).size();
    } else if (!pointsList.empty()) {
        std::vector<Pt> temp(pointsList.begin(), pointsList.end());
        return buildHull(temp).size();
    }
    return 0;
}


/**
 * @brief Computes the convex hull of points (list implementation) and returns
 *        a formatted string containing hull points and area.
 */
std::string State::computeCHList() const {
    std::ostringstream out;
    if (pointsList.size() < 3) {
        out << "0.000000\n";
        return out.str();
    }
    auto start = high_resolution_clock::now();
    std::vector<Pt> temp(pointsList.begin(), pointsList.end());
    auto hull = buildHull(temp);
    double area = polygonArea(hull);
    auto end = high_resolution_clock::now();

    out << "Hull points:\n";
    for (auto &p : hull)
        out << "(" << p.x << ", " << p.y << ")\n";
    out << area << "\n";

    std::cerr << "List: computeCH took "
              << duration_cast<microseconds>(end - start).count() << " us\n";
    return out.str();
}
