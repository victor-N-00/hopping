#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

void merge(vector<int>& array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> left_part(n1), right_part(n2);

    for (int i = 0; i < n1; i++)
        left_part[i] = array[left + i];

    for (int i = 0; i < n2; i++)
        right_part[i] = array[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (left_part[i] <= right_part[j])
            array[k++] = left_part[i++];
        else
            array[k++] = right_part[j++];
    }

    while (i < n1)
        array[k++] = left_part[i++];

    while (j < n2)
        array[k++] = right_part[j++];
}

void mergesort(vector<int>& array, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergesort(array, left, mid);
    mergesort(array, mid + 1, right);

    merge(array, left, mid, right);
}

int main() {
    vector<int> sample_Array = {45, 25, 1, 30, 66};
    int size_arr = sample_Array.size();

    clock_t start = clock();
    mergesort(sample_Array, 0, size_arr - 1);
    clock_t stop = clock();

    long double time = (long double)(stop - start) / CLOCKS_PER_SEC;

    for (int i = 0; i < size_arr; i++)
        cout << sample_Array[i] << " ";

    cout << "\nTime: " << time << " seconds for size " << size_arr << endl;
    return 0;
}

