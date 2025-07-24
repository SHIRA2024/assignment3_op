#include <iostream>
#include <vector>
#include "geom/Hull.hpp"

/**
 * @brief Part 1 main.
 * Reads N points, computes convex hull, prints area.
 */
int main() {
    int n;
    std::cin >> n;
    std::vector<Pt> points(n);
    for (int i = 0; i < n; i++) {
        std::cin >> points[i].x >> points[i].y;
    }

    auto hull = buildHull(points);
    double area = polygonArea(hull);

    std::cout.setf(std::ios::fixed);
    std::cout.precision(6);
    std::cout << area << "\n";
    return 0;
}
