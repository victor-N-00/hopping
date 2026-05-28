#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int unboundedKnapsack(int W, vector<int>& val, vector<int>& wt) {
    int n = val.size();
    vector<int> dp(W + 1, 0);
    
    for (int i = 0; i <= W; i++) {
        for (int j = 0; j < n; j++) {
            if (wt[j] <= i) {
                dp[i] = max(dp[i], dp[i - wt[j]] + val[j]);
            }
        }
    }
    return dp[W];
}

int main() {
    int W = 100;
    vector<int> val = {10, 30, 20};
    vector<int> wt = {5, 10, 15};
    cout << "Max value: " << unboundedKnapsack(W, val, wt) << endl;
    return 0;
}
