#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Interval {
    int start, end;
};

bool compare(Interval a, Interval b) {
    return a.start < b.start;
}

int minIntervalsToCover(vector<Interval>& intervals, int targetStart, int targetEnd) {
    sort(intervals.begin(), intervals.end(), compare);
    int count = 0, i = 0, currentEnd = targetStart;
    
    while (currentEnd < targetEnd) {
        int maxEnd = currentEnd;
        while (i < intervals.size() && intervals[i].start <= currentEnd) {
            maxEnd = max(maxEnd, intervals[i].end);
            i++;
        }
        if (currentEnd == maxEnd) return -1; // Cannot cover
        currentEnd = maxEnd;
        count++;
    }
    return count;
}

int main() {
    vector<Interval> intervals = {{1, 3}, {2, 4}, {3, 6}, {5, 8}};
    cout << "Min intervals: " << minIntervalsToCover(intervals, 1, 7) << endl;
    return 0;
}
