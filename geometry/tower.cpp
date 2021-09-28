#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

struct point {
    double x, y;

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

double dist(point &a, point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

struct circle {
    circle(point point, double r) {
        center = point;
        radius = r;
    }

    point center{};
    double radius;

    bool withoutPoint(point &a) {
        return dist(center, a) > radius;
    }
};

double left_tern(point &a, point &b, point &c) {
    return (c.y - a.y) * (b.x - a.x) - (c.x - a.x) * (b.y - a.y);
}

circle makeCircle(point &a, point &b) {
    point center{(a.x + b.x) / 2.0, (a.y + b.y) / 2.0};
    double radius = dist(center, a);
    return {center, radius};
}

circle circleWithTriangle(point &p1, point &p2, point &p3) {
    double a = p2.x - p1.x;
    double b = p2.y - p1.y;
    double c = p3.x - p1.x;
    double d = p3.y - p1.y;
    double e = a * (p1.x + p2.x) + b * (p1.y + p2.y);
    double f = c * (p1.x + p3.x) + d * (p1.y + p3.y);
    double g = 2 * (a * (p3.y - p2.y) - b * (p3.x - p2.x));
    if (g != 0) {
        point center{};
        double radius;
        center.x = (d * e - b * f) / g;
        center.y = (a * f - c * e) / g;
        radius = dist(center, p1);
        return circle(center, radius);
    } else {
        double p1p2 = dist(p1, p2);
        double p1p3 = dist(p1, p3);
        double p2p3 = dist(p2, p3);
        if (p1p2 > p1p3) {
            if (p1p2 > p2p3) {
                return makeCircle(p1, p2);
            } else {
                return makeCircle(p2, p3);
            }
        } else {
            if (p1p3 > p2p3) {
                return makeCircle(p1, p3);
            } else {
                return makeCircle(p2, p3);
            }
        }
    }

}

circle circleWith2Points(point &p1, point &p2, std::vector<point> &points, int maxInd) {
    circle disc = makeCircle(p1, p2);
    for (int i = 0; i < maxInd; ++i) {
        if (disc.withoutPoint(points[i])) {
            disc = circleWithTriangle(p1, p2, points[i]);
        }
    }
    return disc;
}

circle circleWithPoint(point &p, std::vector<point> &points, int maxInd) {
    std::shuffle(points.begin(), points.begin() + maxInd, std::mt19937(std::random_device()()));
    circle disc = makeCircle(p, points[0]);
    for (int i = 1; i < maxInd; ++i) {
        if (disc.withoutPoint(points[i])) {
            disc = circleWith2Points(p, points[i], points, i);
        }
    }
    return disc;
}

circle returnCircle(std::vector<point> &points) {
    std::shuffle(points.begin(), points.end(), std::mt19937(std::random_device()()));
    int size = points.size();
    if (size > 1) {
        circle disc = makeCircle(points[0], points[1]);
        for (int i = 2; i < size; ++i) {
            if (disc.withoutPoint(points[i])) {
                disc = circleWithPoint(points[i], points, i);
            }
        }
        return disc;
    }
    return {points[0], 0};
}


int main() {
    freopen("tower.in", "r", stdin);
    freopen("tower.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    double x, y;
    std::vector<point> points;
    for (int i = 0; i < n; ++i) {
        std::cin >> x >> y;
        points.push_back(point{x, y});
    }
    circle tower = returnCircle(points);

    std::cout.precision(std::numeric_limits<double>::max_digits10);
    std::cout << tower.radius << "\n";
    std::cout << tower.center.x << " " << tower.center.y << "\n";

    return 0;
}