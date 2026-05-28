#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minSubArrayLen(int target, vector<int>& nums) {
    int n = nums.size();
    int left = 0, sum = 0, minLen = n + 1;
    for (int right = 0; right < n; right++) {
        sum += nums[right];
        while (sum >= target) {
            minLen = min(minLen, right - left + 1);
            sum -= nums[left];
            left++;
        }
    }
    return minLen == n + 1 ? 0 : minLen;
}

int main() {
    vector<int> nums = {2,3,1,2,4,3};
    int target = 7;
    cout << "Minimum length: " << minSubArrayLen(target, nums) << endl;
    return 0;
}
