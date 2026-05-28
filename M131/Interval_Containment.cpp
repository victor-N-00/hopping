#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Interval {
    int start, end;
};

bool compare(Interval a, Interval b) {
    if (a.start == b.start) return a.end > b.end;
    return a.start < b.start;
}

int countUncontained(vector<Interval>& intervals) {
    sort(intervals.begin(), intervals.end(), compare);
    int count = 0, max_end = -1;
    for (auto& i : intervals) {
        if (i.end > max_end) {
            count++;
            max_end = i.end;
        }
    }
    return count;
}

int main() {
    vector<Interval> intervals = {{1, 4}, {2, 3}, {3, 6}};
    cout << "Uncontained intervals: " << countUncontained(intervals) << endl;
    return 0;
}
