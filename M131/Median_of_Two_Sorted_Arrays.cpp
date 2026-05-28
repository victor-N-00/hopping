#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    if (nums1.size() > nums2.size()) return findMedianSortedArrays(nums2, nums1);
    int x = nums1.size(), y = nums2.size();
    int low = 0, high = x;
    while (low <= high) {
        int partitionX = (low + high) / 2;
        int partitionY = (x + y + 1) / 2 - partitionX;
        
        int maxLeftX = (partitionX == 0) ? -1e9 : nums1[partitionX - 1];
        int minRightX = (partitionX == x) ? 1e9 : nums1[partitionX];
        int maxLeftY = (partitionY == 0) ? -1e9 : nums2[partitionY - 1];
        int minRightY = (partitionY == y) ? 1e9 : nums2[partitionY];
        
        if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
            if ((x + y) % 2 == 0)
                return ((double)max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2;
            else
                return (double)max(maxLeftX, maxLeftY);
        } else if (maxLeftX > minRightY) {
            high = partitionX - 1;
        } else {
            low = partitionX + 1;
        }
    }
    return 0.0;
}

int main() {
    vector<int> a = {1, 3}, b = {2};
    cout << "Median: " << findMedianSortedArrays(a, b) << endl;
    return 0;
}
