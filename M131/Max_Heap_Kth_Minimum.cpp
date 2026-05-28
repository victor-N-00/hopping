#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int findKthMinimum(vector<int>& nums, int k) {
    priority_queue<int> maxHeap;
    for (int x : nums) {
        maxHeap.push(x);
        if (maxHeap.size() > k) {
            maxHeap.pop();
        }
    }
    return maxHeap.top();
}

int main() {
    vector<int> nums = {7, 10, 4, 3, 20, 15};
    int k = 3;
    cout << k << "rd minimum: " << findKthMinimum(nums, k) << endl;
    return 0;
}
