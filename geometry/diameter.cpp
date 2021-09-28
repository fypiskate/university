#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
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

    point operator+(const point &other) const {
        return point{x + other.x, y + other.y};
    }

    point operator-(const point &other) const {
        return point{x - other.x, y - other.y};
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
    long long max_dist(0), tern, dist;
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

long long dist(point &a, point &b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

long long maxDist = 0;

void updAns(point &a, point &b) {
    long long curDist = dist(a, b);
    if (curDist > maxDist) {
        maxDist = curDist;
    }
}

void find_diameter(std::vector<point> &convex_hull) {
    int size = convex_hull.size();
    int left(0), right(0);
    for (int i = 0; i < size; ++i) {
        if (convex_hull[i].x < convex_hull[left].x) {
            left = i;
        } else if (convex_hull[i].x > convex_hull[right].x) {
            right = i;
        }
    }
    int fstColiper = left, sndColiper = right;
    point a{}, b{}, c{};
    long long tern;
    int difLeft = 0, difRight = 0;
    while (true) {
        updAns(convex_hull[fstColiper], convex_hull[sndColiper]);
        int nextFst = (fstColiper + 1) % size;
        int nextSnd = (sndColiper + 1) % size;
        a = convex_hull[fstColiper];
        b = convex_hull[nextFst];
        c = convex_hull[fstColiper] + convex_hull[nextSnd] - convex_hull[sndColiper];
        tern = left_tern(a, b, c);
        if (tern == 0) {
            fstColiper = nextFst;
            sndColiper = nextSnd;
            ++difLeft;
            ++difRight;
        } else if (tern < 0) {
            sndColiper = nextSnd;
            ++difRight;
        } else {
            fstColiper = nextFst;
            ++difLeft;
        }
        if ((difLeft > 0 && fstColiper == left) || (difRight > 0 && sndColiper == right))
            break;
    }
}

int main() {
    freopen("diameter.in", "r", stdin);
    freopen("diameter.out", "w", stdout);

    long long n;
    std::cin >> n;
    long long x, y;
    std::vector<point> points;
    for (long long i = 0; i < n; ++i) {
        std::cin >> x >> y;
        points.push_back(point{x, y});
    }
    std::sort(points.begin(), points.end());
    std::set<point> convex_up, convex_down;
    convex_up.insert(points[0]);
    convex_up.insert(points[n - 1]);

    hull(points[0], points[n - 1], 1, points, convex_up);
    hull(points[0], points[n - 1], -1, points, convex_down);
    std::vector<point> convex;
    for (auto p : convex_up) {
        convex.push_back(p);
    }
    for (auto p = convex_down.rbegin(); p != convex_down.rend(); ++p) {
        convex.push_back(*p);
    }

    updAns(convex[0], convex[convex.size() - 1]);
    find_diameter(convex);
    std::cout.precision(std::numeric_limits<double>::max_digits10);
    std::cout << std::sqrt(maxDist);

    return 0;
}