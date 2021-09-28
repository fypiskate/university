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

bool cmpY(const point &a, const point &b) {
    return a.y < b.y;
}

std::pair<point, point> algo(std::vector<point> &points) {
    if (points.size() == 2)
        return std::make_pair(points[0], points[1]);
    if (points.size() == 3) {
        long long distAB = dist(points[0], points[1]);
        long long distBC = dist(points[1], points[2]);
        long long distAC = dist(points[0], points[2]);
        if (distAB < distBC) {
            if (distAB < distAC) {
                return std::make_pair(points[0], points[1]);
            } else {
                return std::make_pair(points[0], points[2]);
            }
        } else {
            if (distBC < distAC) {
                return std::make_pair(points[1], points[2]);
            } else {
                return std::make_pair(points[0], points[1]);
            }
        }
    }
    long long minDist;
    int mid = points.size() / 2;
    std::vector<point> left(points.begin(), points.begin() + mid);
    std::pair<point, point> leftAns = algo(left);
    std::vector<point> right(points.begin() + mid, points.end());
    std::pair<point, point> rightAns = algo(right);
    long long distLeft = dist(leftAns.first, leftAns.second);
    long long distRight = dist(rightAns.first, rightAns.second);
    std::pair<point, point> answer;
    if (distLeft < distRight) {
        minDist = distLeft;
        answer = leftAns;
    } else {
        minDist = distRight;
        answer = rightAns;
    }
    std::vector<point> epsilon;
    epsilon.push_back(points[mid]);
    int ind = 1;
    while (mid - ind >= 0 && minDist > (points[mid].x - points[mid - ind].x) * (points[mid].x - points[mid - ind].x)) {
        epsilon.push_back(points[mid - ind]);
        ++ind;
    }
    ind = 1;
    while (mid + ind < points.size() &&
           minDist > (points[mid].x - points[mid + ind].x) * (points[mid].x - points[mid + ind].x)) {
        epsilon.push_back(points[mid + ind]);
        ++ind;
    }

    std::sort(epsilon.begin(), epsilon.end(), cmpY);
    for (int i = 0; i < epsilon.size(); ++i) {
//        for (int next = i + 1;
//             next < epsilon.size() && (minDist > (epsilon[next].y - epsilon[i].y) * (epsilon[next].y - epsilon[i].y))
//             && (minDist > dist(epsilon[next], epsilon[i])); ++next) {
        for (int next = i + 1; next < 15 && next < epsilon.size(); ++next) {
            if (minDist > dist(epsilon[next], epsilon[i])) {
                minDist = dist(epsilon[next], epsilon[i]);
                answer = std::make_pair(epsilon[next], epsilon[i]);
            }
        }
    }

    return answer;
}

int main() {
    freopen("rendezvous.in", "r", stdin);
    freopen("rendezvous.out", "w", stdout);
    int n;
    std::cin >> n;
    std::vector<point> points(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> points[i].x >> points[i].y;
    }
    std::sort(points.begin(), points.end());
    std::pair<point, point> ans = algo(points);
    std::cout << ans.first.x << " " << ans.first.y << " " << ans.second.x << " " << ans.second.y;
    return 0;
}