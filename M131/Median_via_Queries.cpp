#include <iostream>
using namespace std;

// Mock rank query
int queryRank(int x) {
    return x; // returns rank in an imaginary dataset
}

int findMedian(int low, int high, int n) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int rank = queryRank(mid);
        if (rank == n / 2) return mid;
        else if (rank < n / 2) low = mid + 1;
        else high = mid - 1;
    }
    return low;
}

int main() {
    cout << "Median via Queries simulation." << endl;
    return 0;
}
