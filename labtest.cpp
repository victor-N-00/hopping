#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
using namespace std;

int ED(string& str1,string& str2) {
    int m = str1.size();
    int n = str2.size();

    vector<vector<int>>dp(m + 1, vector<int>(n + 1));

    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int cost = (str1[i - 1] == str2[j - 1]) ? 0 : 1;
            int inter=min(dp[i - 1][j],dp[i][j - 1]);
            dp[i][j] = min(inter,dp[i - 1][j - 1] + cost);
        }
    }

    return dp[m][n];
}

int main() {
    string s1,s2;
    s1="horse";
    s2="ros";

    int editDistanceValue = ED(s1, s2);
    cout<<editDistanceValue<<endl;

    return 0;
}