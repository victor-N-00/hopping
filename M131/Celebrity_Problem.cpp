#include <iostream>
#include <vector>
using namespace std;

int findCelebrity(vector<vector<int>>& knows, int n) {
    int candidate = 0;
    for (int i = 1; i < n; i++) {
        if (knows[candidate][i]) {
            candidate = i;
        }
    }
    for (int i = 0; i < n; i++) {
        if (i != candidate && (knows[candidate][i] || !knows[i][candidate])) {
            return -1;
        }
    }
    return candidate;
}

int main() {
    vector<vector<int>> matrix = {{0,1,0},{0,0,0},{0,1,0}};
    cout << "Celebrity is person: " << findCelebrity(matrix, 3) << endl;
    return 0;
}
