#include <iostream>
#include <vector>
using namespace std;

int mergeSortAndCount(vector<int>& arr, int left, int right) {
    if (left >= right) return 0;
    int mid = left + (right - left) / 2;
    int count = mergeSortAndCount(arr, left, mid) + mergeSortAndCount(arr, mid + 1, right);
    
    int j = mid + 1;
    for (int i = left; i <= mid; i++) {
        while (j <= right && arr[i] > 2LL * arr[j]) {
            j++;
        }
        count += (j - (mid + 1));
    }
    
    vector<int> temp(right - left + 1);
    int i = left, k = 0; j = mid + 1;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (int p = 0; p < k; p++) arr[left + p] = temp[p];
    
    return count;
}

int main() {
    vector<int> nums = {2, 4, 1, 3, 5};
    cout << "Significant Inversions: " << mergeSortAndCount(nums, 0, nums.size() - 1) << endl;
    return 0;
}
