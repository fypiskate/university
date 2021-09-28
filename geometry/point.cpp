#include <iostream>
#include <vector>

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

long long left_tern(point &a, point &b, point &c) {
    return (c.y - a.y) * (b.x - a.x) - (c.x - a.x) * (b.y - a.y);
}

int sgn(long long x) {
    return (x > 0) - (x < 0);
}

int check(std::vector<point> &points, point q) {
    int size = points.size();
    int count = 0;
    for (int i = 0; i < size; ++i) {
        point a = points[i];
        point b = points[(i + 1) % size];
        int tern = sgn(left_tern(a, b, q));
        if (a.y > b.y)
            std::swap(a, b);
        if (tern == 0 && q.y >= a.y && q.y <= b.y)
            return 1;
        if (a.y == b.y || q.y <= a.y || q.y > b.y)
            continue;
        if (q.y == b.y && q.x < a.x)
            ++count;
        if ((sgn(left_tern(a, b, q)) > 0) && (q.y >= a.y) && (q.y <= b.y))
            ++count;
    }
    return count;
}

int main() {
    freopen("point.in", "r", stdin);
    freopen("point.out", "w", stdout);

    unsigned int n;
    std::cin >> n;
    std::vector<point> poligon(n);
    point q{};
    std::cin >> q.x >> q.y;
    for (int i = 0; i < n; ++i) {
        std::cin >> poligon[i].x >> poligon[i].y;
    }

    if (check(poligon, q) % 2)
        std::cout << "YES";
    else
        std::cout << "NO";

    return 0;
}
