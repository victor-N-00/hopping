#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Job {
    char id;
    int deadline, profit;
};

bool compare(Job a, Job b) {
    return a.profit > b.profit;
}

void printJobScheduling(vector<Job>& jobs, int n) {
    sort(jobs.begin(), jobs.end(), compare);
    vector<int> result(n, -1);
    vector<bool> slot(n, false);
    
    int total_profit = 0;
    for (int i = 0; i < n; i++) {
        for (int j = min(n, jobs[i].deadline) - 1; j >= 0; j--) {
            if (!slot[j]) {
                result[j] = i;
                slot[j] = true;
                total_profit += jobs[i].profit;
                break;
            }
        }
    }
    
    cout << "Jobs sequence: ";
    for (int i = 0; i < n; i++) {
        if (slot[i]) cout << jobs[result[i]].id << " ";
    }
    cout << "\nTotal Profit: " << total_profit << endl;
}

int main() {
    vector<Job> jobs = {{'a', 2, 100}, {'b', 1, 19}, {'c', 2, 27}, {'d', 1, 25}, {'e', 3, 15}};
    printJobScheduling(jobs, jobs.size());
    return 0;
}
