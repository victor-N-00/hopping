#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Line {
    double m, c; // y = mx + c
};

bool compareLines(Line l1, Line l2) {
    if (l1.m == l2.m) return l1.c > l2.c;
    return l1.m < l2.m;
}

// Example representation for finding visible lines (Convex Hull Trick)
void findVisibleLines(vector<Line>& lines) {
    sort(lines.begin(), lines.end(), compareLines);
    cout << "Visible lines evaluated." << endl;
}

int main() {
    vector<Line> lines = {{2, 3}, {1, 5}, {2, 4}};
    findVisibleLines(lines);
    return 0;
}
