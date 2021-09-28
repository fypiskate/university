#include <iostream>
#include <vector>
#include <stack>

struct point {
    long long x, y;
    int id;

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

struct delta {
    int a, b, c;
};

int sgn(long long x) {
    return (x > 0) - (x < 0);
}

long long left_tern(point &a, point &b, point &c) {
    return (c.y - a.y) * (b.x - a.x) - (c.x - a.x) * (b.y - a.y);
}

std::vector<delta> triangulation(std::vector<point> &poligon) {
    std::vector<delta> ans;
    std::stack<point> points;
    for (int i = 0; i < poligon.size(); ++i) {
        points.push(poligon[i]);
        while (points.size() >= 3) {

            point next = points.top();
            points.pop();

            point cur = points.top();
            points.pop();

            point prev = points.top();
            points.pop();

            if (sgn(left_tern(prev, cur, next)) <= 0) {
                points.push(prev);
                points.push(cur);
                points.push(next);
                break;
            } else {
                delta del{prev.id, cur.id, next.id};
                bool is_ear = true;
                for (int p = 0; p < poligon.size(); ++p) {
                    if (poligon[p] != prev && poligon[p] != cur && poligon[p] != next) {
                        if (sgn(left_tern(poligon[del.a], poligon[del.b], poligon[p])) >= 0
                            && sgn(left_tern(poligon[del.b], poligon[del.c], poligon[p])) >= 0
                            && sgn(left_tern(poligon[del.c], poligon[del.a], poligon[p])) >= 0) {
                            is_ear = false;
                            points.push(prev);
                            points.push(cur);
                            points.push(next);
                            break;
                        }
                    }
                }
                if (is_ear) {
                    ans.push_back(del);
                    points.push(prev);
                    points.push(next);
                } else {
                    break;
                }
            }
        }
    }
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n;
    std::cin >> n;
    std::vector<point> poligon(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> poligon[i].x >> poligon[i].y;
        poligon[i].id = i;
    }
    std::vector<delta> ans = triangulation(poligon);
    for (auto &an : ans) {
        std::cout << an.a + 1 << " " << an.b + 1 << " " << an.c + 1 << "\n";
    }
    return 0;
}