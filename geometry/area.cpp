#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

const double eps = 0.000001;
const double zero = 0.0000001;
const long long border = 1000000000;

struct point {
    double x, y;

    point(double x, double y) : x(x), y(y) {};

    point() : x(0), y(0) {};

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

struct halfplane {
    double a, b, c;

    halfplane() : a(0), b(0), c(0) {};

    halfplane(double a, double b, double c) : a(a), b(b), c(c) {};

    halfplane(point &p1, point &p2) {
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = p1.y * p2.x - p1.x * p2.y;
    }

};


bool inPlane(point &p, halfplane &plane) {
    return (plane.a * p.x + plane.b * p.y + plane.c > zero);
}

point findIntersection(halfplane &p1, halfplane &p2) {
    double d1 = p1.a * p2.b - p1.b * p2.a;
    double d2 = p1.b * p2.c - p1.c * p2.b;
    double d3 = p1.a * p2.c - p1.c * p2.a;
    return {d2 / d1, -d3 / d1};
}

double delta_area(point &a, point &b, point &c) {
    return fabs((a.x - c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x)) / 2.0;
}

double calc_area(std::vector<point> &points) {
    long long size = points.size();
    if (size == 0)
        return 0;
    else {
        point start = points[0];
        double area = 0;
        for (long long i = 1; i < size - 1; ++i) {
            area += delta_area(start, points[i], points[i + 1]);
        }
        return area;
    }
}

std::vector<point> findPlane(std::vector<point> &poligon, halfplane &line) {
    std::vector<point> ans;
    for (long long i = 0; i < poligon.size(); ++i) {
        point first = poligon[(i + 1) % poligon.size()];
        point second = poligon[i];
        bool statusFirst = inPlane(first, line);
        bool statusSecond = inPlane(second, line);

        if (statusFirst && statusSecond) {
            if (ans.empty() || second != ans[ans.size() - 1])
                ans.push_back(second);
        }
        if (statusFirst && !statusSecond) {
            halfplane fsline = halfplane(first, second);
            point inter = findIntersection(line, fsline);
            if (ans.empty() || inter != ans[ans.size() - 1])
                ans.push_back(inter);
        }
        if (!statusFirst && statusSecond) {
            halfplane fsline = halfplane(first, second);
            point inter = findIntersection(line, fsline);
            if (ans.empty() || second != ans[ans.size() - 1])
                ans.push_back(second);
            if (ans.empty() || inter != ans[ans.size() - 1])
                ans.push_back(inter);
        }
    }
    return ans;
}

bool eqZero(double d) {
    return (d > 0 - eps && d < 0 + eps);
}

bool checkForInfinity(std::vector<point> &poligon) {
    halfplane p1(1, 0, -border);
    halfplane p2(0, 1, -border);
    halfplane p3(-1, 0, -border);
    halfplane p4(0, -1, -border);
    for (auto &i : poligon) {
        if (eqZero(p1.a * i.x + p1.b * i.y + p1.c)
            || eqZero(p2.a * i.x + p2.b * i.y + p2.c)
            || eqZero(p3.a * i.x + p3.b * i.y + p3.c)
            || eqZero(p4.a * i.x + p4.b * i.y + p4.c)) {
            return true;
        }
    }
    return false;
}


int main() {
    freopen("area.in", "r", stdin);
    freopen("area.out", "w", stdout);

    long long n;
    std::cin >> n;
    std::vector<halfplane> lines(n);
    for (long long i = 0; i < n; ++i) {
        std::cin >> lines[i].a >> lines[i].b >> lines[i].c;
    }

    std::vector<point> poligon;
    poligon.emplace_back(border, border);
    poligon.emplace_back(-border, border);
    poligon.emplace_back(-border, -border);
    poligon.emplace_back(border, -border);


    for (long long i = 0; i < n; ++i) {
        poligon = findPlane(poligon, lines[i]);
    }
    if (checkForInfinity(poligon))
        std::cout << "-1";
    else {
        double ans = calc_area(poligon);
        std::cout << std::setprecision(13) << ans;
    }
    return 0;
}