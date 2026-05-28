#include <bits/stdc++.h>
using namespace std;

int editDistance(string x, string y) {
    int n = x.size(), m = y.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Base cases
    for (int j = 0; j <= m; j++)
        dp[n][j] = m - j;

    for (int i = 0; i <= n; i++)
        dp[i][m] = n - i;

    // Fill from bottom-right to top-left
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {

            if (x[i] == y[j]) {
                dp[i][j] = dp[i + 1][j + 1];
            } else {
                int del = dp[i + 1][j];     // delete
                int ins = dp[i][j + 1];     // insert
                int rep = dp[i + 1][j + 1]; // replace

                dp[i][j] = 1 + min({del, ins, rep});
            }
        }
    }

    return dp[0][0];
}

int main() {
    string x = "horse", y = "ros";
    cout << editDistance(x, y) << endl;
}