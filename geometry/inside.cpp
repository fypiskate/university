#include <iostream>
#include <vector>
#include <algorithm>

struct point {
    long long x, y;

    bool operator==(const point &other) const {
        return x == other.x && y == other.y;
    }

};

long long left_tern(point &a, point &b, point &c) {
    return (c.y - a.y) * (b.x - a.x) - (c.x - a.x) * (b.y - a.y);
}

int sgn(long long &x) {
    return (x > 0) - (x < 0);
}

int get_position(std::vector<point> &poligon, point q) {
    point zero = poligon[0];
    int size = poligon.size();

    long long tern1 = left_tern(zero, poligon[1], q);
    long long terns = left_tern(zero, poligon[size - 1], q);
    if (tern1 < 0 || terns > 0)
        return -1;

    int first = 1, last = size - 1;
    while (first < last - 1) {
        int mid = (first + last) / 2;
        if (left_tern(zero, poligon[mid], q) > 0) {
            first = mid;
        } else {
            last = mid;
        }
    }
    long long tern = left_tern(poligon[first], poligon[last], q);
    if (sgn(tern) > 0) {
        if (q == zero || tern1 == 0 || terns == 0)
            return 0;
        return 1;
    }
    return sgn(tern);

}

int main() {
    freopen("inside.in", "r", stdin);
    freopen("inside.out", "w", stdout);

    int n;
    std::cin >> n;
    std::vector<point> poligon(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> poligon[i].x >> poligon[i].y;
    }

    if (left_tern(poligon[0], poligon[1], poligon[2]) < 0) {
        std::reverse(poligon.begin() + 1, poligon.end());
    }

    int k;
    std::cin >> k;
    for (int i = 0; i < k; ++i) {
        point q{};
        std::cin >> q.x >> q.y;
        int ans = get_position(poligon, q);
        switch (ans) {
            case 1:
                std::cout << "INSIDE\n";
                break;
            case 0:
                std::cout << "BORDER\n";
                break;
            case -1:
                std::cout << "OUTSIDE\n";
                break;
            default:
                std::cout << "error\n";
                break;
        }
    }

    return 0;
}