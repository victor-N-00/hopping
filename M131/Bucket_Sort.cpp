#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void bucketSort(vector<float>& arr) {
    int n = arr.size();
    if(n <= 0) return;
    vector<vector<float>> buckets(n);
    
    for (int i = 0; i < n; i++) {
        int bi = n * arr[i];
        if (bi >= n) bi = n - 1;
        buckets[bi].push_back(arr[i]);
    }
    
    for (int i = 0; i < n; i++) {
        sort(buckets[i].begin(), buckets[i].end());
    }
    
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            arr[index++] = buckets[i][j];
        }
    }
}

int main() {
    vector<float> arr = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    bucketSort(arr);
    cout << "Sorted array: ";
    for(float x : arr) cout << x << " ";
    cout << endl;
    return 0;
}
