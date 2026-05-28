#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solveEggDrop(int n, int k) {
    vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));
    int m = 0;
    while (dp[m][n] < k) {
        m++;
        for (int i = 1; i <= n; i++) {
            dp[m][i] = dp[m - 1][i - 1] + dp[m - 1][i] + 1;
        }
    }
    return m;
}

int main() {
    int floors = 100, eggs = 2;
    cout << "Minimum drops for " << floors << " floors and " << eggs << " eggs: " << solveEggDrop(eggs, floors) << endl;
    return 0;
}
