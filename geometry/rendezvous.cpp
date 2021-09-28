#include <iostream>
#include <vector>
#include <algorithm>


struct point {
    long long x, y;

    bool operator<(const point &other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

long long dist(point &a, point &b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

long long minDist = INT64_MAX;
point ansA, ansB;
std::vector<point> points, tmp;
int n, tmpSize(0);

inline void updAns(point &a, point &b) {
    long long curDist = dist(a, b);
    if (minDist > curDist) {
        minDist = curDist;
        ansA = a;
        ansB = b;
    }
}

bool cmpY(const point &a, const point &b) {
    return a.y < b.y;
}

void algo(int l, int r) {
    if (r - l > 3) {
        int m = (l + r) / 2;
        long long midx = points[m].x;

        algo(l, m);
        algo(m + 1, r);


        std::merge(points.begin() + l, points.begin() + m + 1, points.begin() + m + 1, points.begin() + r + 1,
                   tmp.begin(), &cmpY);
        std::copy(tmp.begin(), tmp.begin() + r - l + 1, points.begin() + l);
        tmpSize = 0;

        for (int i = l; i < r + 1; ++i) {
            long long pix = points[i].x;
            if (minDist > (pix - midx) * (pix - midx)) {
                for (int j = tmpSize - 1; j >= 0; --j) {
                    if (minDist > points[i].y - tmp[j].y)
                        updAns(points[i], tmp[j]);
                    else
                        break;
                }
                tmp[tmpSize] = points[i];
                ++tmpSize;
            }
        }
    } else {
        for (int i = l; i <= r; ++i) {
            for (int j = i + 1; j <= r; ++j) {
                updAns(points[i], points[j]);
            }
        }
        std::sort(points.begin() + l, points.begin() + r + 1, &cmpY);
        return;
    }
}

int main() {
    freopen("rendezvous.in", "r", stdin);
    freopen("rendezvous.out", "w", stdout);

    std::cin >> n;
    points.resize(n);
    tmp.resize(n);
    for (int i = 0; i < n; ++i) {
        long long a, b;
        std::cin >> a >> b;
        points[i].x = a;
        points[i].y = b;
    }
    std::sort(points.begin(), points.end());

    algo(0, n - 1);

    std::cout << ansA.x << " " << ansA.y << " " << ansB.x << " " << ansB.y;

    fclose(stdin);
    fclose(stdout);

    return 0;
}