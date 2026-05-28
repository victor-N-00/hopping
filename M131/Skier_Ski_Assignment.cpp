#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int minAssignmentCost(vector<int>& skiers, vector<int>& skis) {
    sort(skiers.begin(), skiers.end());
    sort(skis.begin(), skis.end());
    int total_diff = 0;
    for (int i = 0; i < skiers.size(); i++) {
        total_diff += abs(skiers[i] - skis[i]);
    }
    return total_diff;
}

int main() {
    vector<int> skiers = {1, 3, 5};
    vector<int> skis = {2, 5, 6};
    cout << "Min assignment cost: " << minAssignmentCost(skiers, skis) << endl;
    return 0;
}
