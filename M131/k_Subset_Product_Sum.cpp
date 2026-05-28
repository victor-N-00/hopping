#include <iostream>
#include <vector>
using namespace std;

int kSubsetProductSum(vector<int>& nums, int k) {
    vector<int> dp(k + 1, 0);
    dp[0] = 1;
    for (int x : nums) {
        for (int i = k; i >= 1; i--) {
            dp[i] = dp[i] + dp[i - 1] * x;
        }
    }
    return dp[k];
}

int main() {
    vector<int> nums = {1, 2, 3};
    int k = 2;
    cout << "Sum of " << k << "-subset products: " << kSubsetProductSum(nums, k) << endl;
    return 0;
}
