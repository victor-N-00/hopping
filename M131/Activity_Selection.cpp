#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Activity {
    int start, finish;
};

bool compare(Activity a, Activity b) {
    return a.finish < b.finish;
}

void printMaxActivities(vector<Activity>& arr) {
    sort(arr.begin(), arr.end(), compare);
    cout << "Selected Activities: (" << arr[0].start << ", " << arr[0].finish << ") ";
    
    int i = 0;
    for (int j = 1; j < arr.size(); j++) {
        if (arr[j].start >= arr[i].finish) {
            cout << "(" << arr[j].start << ", " << arr[j].finish << ") ";
            i = j;
        }
    }
    cout << endl;
}

int main() {
    vector<Activity> arr = {{5, 9}, {1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}};
    printMaxActivities(arr);
    return 0;
}
