#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int lengthOfLIS(vector<int>& nums) {
    vector<int> res;
    for (int x : nums) {
        auto it = lower_bound(res.begin(), res.end(), x);
        if (it == res.end()) res.push_back(x);
        else *it = x;
    }
    return res.size();
}

int main() {
    vector<int> nums = {10,9,2,5,3,7,101,18};
    cout << "LIS length: " << lengthOfLIS(nums) << endl;
    return 0;
}
