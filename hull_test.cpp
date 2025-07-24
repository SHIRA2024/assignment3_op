#include <bits/stdc++.h>
using namespace std;

struct Pt { double x, y; };

static double cross(const Pt& a, const Pt& b, const Pt& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

vector<Pt> buildHull(vector<Pt>& pts) {
    int n = pts.size();
    if (n < 3) return pts;

    vector<Pt> hull;
    int l = 0;
    for (int i = 1; i < n; i++) {
        if (pts[i].x < pts[l].x || 
           (pts[i].x == pts[l].x && pts[i].y < pts[l].y))
            l = i;
    }

    int p = l, q;
    do {
        hull.push_back(pts[p]);
        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            if (cross(pts[p], pts[i], pts[q]) > 0)
                q = i;
        }
        p = q;
    } while (p != l);
    return hull;
}

double polygonArea(const vector<Pt>& poly) {
    double area = 0.0;
    for (int i = 0, n = poly.size(); i < n; i++) {
        int j = (i + 1) % n;
        area += poly[i].x * poly[j].y - poly[j].x * poly[i].y;
    }
    return fabs(area) / 2.0;
}

int main() {
    int n;
    cin >> n;
    vector<Pt> points(n);
    for (int i = 0; i < n; i++) cin >> points[i].x >> points[i].y;

    auto hull = buildHull(points);
    cerr << "Hull points (CCW debug):\n";
    for (auto &p : hull) cerr << "(" << p.x << ", " << p.y << ")\n";

    cout << fixed << setprecision(6) << polygonArea(hull) << "\n";
}
