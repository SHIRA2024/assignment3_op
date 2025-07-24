#pragma once

#include <vector>
#include <list>
#include <string>
#include "geom/Point.hpp"

/**
 * @brief Class that stores and manages a set of 2D points.
 *        It supports both vector and list implementations for flexibility.
 */
class State {
private:
    std::vector<Pt> points;      ///< Container for vector-based implementation.
    std::list<Pt> pointsList;    ///< Container for list-based implementation.

public:
    // ------------------- VECTOR IMPLEMENTATION -------------------
    int getCHSize() const;
    /**
     * @brief Initializes a new graph (vector-based).
     * @param n Capacity hint for the vector container.
     */
    void newGraphVector(int n);

    /**
     * @brief Adds a point (x, y) to the vector-based container.
     */
    void addPointVector(double x, double y);

    /**
     * @brief Removes a point (x, y) from the vector-based container.
     */
    void removePointVector(double x, double y);

    /**
     * @brief Computes the convex hull of vector-based points.
     * @return A string with hull points and area.
     */
    std::string computeCHVector() const;

    // ------------------- LIST IMPLEMENTATION -------------------

    /**
     * @brief Initializes a new graph (list-based).
     * @param n Ignored (lists do not have pre-allocation).
     */
    void newGraphList(int n);

    /**
     * @brief Adds a point (x, y) to the list-based container.
     */
    void addPointList(double x, double y);

    /**
     * @brief Removes a point (x, y) from the list-based container.
     */
    void removePointList(double x, double y);

    /**
     * @brief Computes the convex hull of list-based points.
     * @return A string with hull points and area.
     */
    std::string computeCHList() const;
};
