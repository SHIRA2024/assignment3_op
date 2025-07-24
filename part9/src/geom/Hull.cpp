#include "geom/Hull.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>

/**
 * @brief Cross product (b - a) x (c - a).
 */
static double cross(const Pt& a, const Pt& b, const Pt& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

/**
 * @brief Builds the convex hull using the Graham Scan algorithm.
 * @param pts Vector of points.
 * @return Convex hull points in counter-clockwise order.
 */
std::vector<Pt> buildHull(const std::vector<Pt>& pts) {
    std::vector<Pt> sortedPts = pts;  // Work on a copy
    constexpr double EPS = 1e-9;

    if (sortedPts.size() <= 1) return sortedPts;

    // Find pivot (lowest y, then lowest x)
    auto pivot = *std::min_element(sortedPts.begin(), sortedPts.end(),
        [](const Pt& a, const Pt& b) {
            return (a.y < b.y) || (a.y == b.y && a.x < b.x);
        });

    // Sort points by polar angle from pivot
    std::sort(sortedPts.begin(), sortedPts.end(), [pivot](const Pt& a, const Pt& b) {
        double angleA = atan2(a.y - pivot.y, a.x - pivot.x);
        double angleB = atan2(b.y - pivot.y, b.x - pivot.x);
        if (fabs(angleA - angleB) < EPS) {
            double distA = hypot(a.x - pivot.x, a.y - pivot.y);
            double distB = hypot(b.x - pivot.x, b.y - pivot.y);
            return distA < distB;
        }
        return angleA < angleB;
    });

    // Graham Scan
    std::vector<Pt> hull;
    for (const auto& p : sortedPts) {
        while (hull.size() >= 2 &&
               cross(hull[hull.size() - 2], hull.back(), p) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    }

    // Output hull points
    std::cout << "Hull points:\n";
    for (const auto& p : hull) {
        std::cout << "(" << p.x << ", " << p.y << ")\n";
    }

    return hull;
}

/**
 * @brief Computes the area of a polygon using the Shoelace formula.
 */
double polygonArea(const std::vector<Pt>& poly) {
    double area = 0.0;
    int n = poly.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += poly[i].x * poly[j].y - poly[j].x * poly[i].y;
    }
    return std::fabs(area) / 2.0;
}
