#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
};

bool comparePoints(Point p1, Point p2) {
    if (p1.x == p2.x) return p1.y > p2.y;
    return p1.x > p2.x;
}

vector<Point> getNonDominated(vector<Point>& points) {
    sort(points.begin(), points.end(), comparePoints);
    vector<Point> result;
    int maxY = -1e9;
    for (auto& p : points) {
        if (p.y >= maxY) {
            result.push_back(p);
            maxY = p.y;
        }
    }
    return result;
}

int main() {
    vector<Point> points = {{1, 4}, {2, 2}, {3, 1}, {4, 3}};
    vector<Point> res = getNonDominated(points);
    cout << "Non dominated points: ";
    for (auto& p : res) cout << "(" << p.x << "," << p.y << ") ";
    cout << endl;
    return 0;
}
