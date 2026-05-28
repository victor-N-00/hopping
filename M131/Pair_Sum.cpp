#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool hasPairSum(vector<int>& arr, int target) {
    sort(arr.begin(), arr.end());
    int left = 0, right = arr.size() - 1;
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == target) return true;
        else if (sum < target) left++;
        else right--;
    }
    return false;
}

int main() {
    vector<int> arr = {1, 4, 45, 6, 10, -8};
    int target = 16;
    cout << "Has Pair: " << (hasPairSum(arr, target) ? "Yes" : "No") << endl;
    return 0;
}
