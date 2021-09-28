#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

struct point {
    long long x, y;

    bool operator==(const point &other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const point &other) const {
        return x != other.x || y != other.y;
    }

    bool operator<(const point &other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

int sgn(long long &x) {
    return (x > 0) - (x < 0);
}

long long left_tern(point &a, point &b, point &c) {
    return (c.y - a.y) * (b.x - a.x) - (c.x - a.x) * (b.y - a.y);
}

void hull(point &left_p, point &right_p, int side, std::vector<point> &pts, std::set<point> &convex_hull) {
    if (pts.empty())
        return;
    std::vector<point> new_pts;
    long long max_dist(INT64_MIN), tern, dist;
    point max_point = left_p;
    for (auto &pt : pts) {
        tern = left_tern(left_p, right_p, pt);
        dist = llabs(tern);
        if (sgn(tern) == side) {
            new_pts.push_back(pt);
            if (dist > max_dist) {
                max_dist = dist;
                max_point = pt;
            }
        }
    }
    if (max_point != left_p) {
        convex_hull.insert(max_point);
    }
    hull(left_p, max_point, side, new_pts, convex_hull);
    hull(max_point, right_p, side, new_pts, convex_hull);

}

int main() {
    freopen("hull.in", "r", stdin);
    freopen("hull.out", "w", stdout);

    int n;
    std::cin >> n;
    long long x, y;
    std::vector<point> points;
    for (int i = 0; i < n; ++i) {
        std::cin >> x >> y;
        points.push_back(point{x, y});
    }
    std::sort(points.begin(), points.end());
    std::set<point> convex_up, convex_down;
    convex_up.insert(points[0]);
    convex_up.insert(points[n - 1]);

    hull(points[0], points[n - 1], 1, points, convex_up);
    hull(points[0], points[n - 1], -1, points, convex_down);

    std::cout << convex_up.size() + convex_down.size() << "\n";
    for (auto p : convex_up) {
        std::cout << p.x << " " << p.y << "\n";
    }
    for (auto p = convex_down.rbegin(); p != convex_down.rend(); ++p) {

        std::cout << (*p).x << " " << (*p).y << "\n";
    }

    return 0;
}