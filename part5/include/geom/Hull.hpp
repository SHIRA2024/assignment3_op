#pragma once
#include <vector>
#include "Point.hpp"

/**
 * @brief Builds the convex hull of a set of 2D points using Graham Scan.
 * @param pts Vector of points (input points are not modified).
 * @return Convex hull points in counter-clockwise order.
 */
std::vector<Pt> buildHull(const std::vector<Pt>& pts);

/**
 * @brief Computes the area of a polygon using the Shoelace formula.
 * @param poly Vector of points representing the polygon (in order).
 * @return Area of the polygon.
 */
double polygonArea(const std::vector<Pt>& poly);
