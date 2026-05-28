#include <iostream>
#include <vector>
using namespace std;

int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int total_tank = 0, curr_tank = 0, start_station = 0;
    for (int i = 0; i < gas.size(); i++) {
        total_tank += gas[i] - cost[i];
        curr_tank += gas[i] - cost[i];
        if (curr_tank < 0) {
            start_station = i + 1;
            curr_tank = 0;
        }
    }
    return total_tank >= 0 ? start_station : -1;
}

int main() {
    vector<int> gas = {1,2,3,4,5};
    vector<int> cost = {3,4,5,1,2};
    cout << "Start at station: " << canCompleteCircuit(gas, cost) << endl;
    return 0;
}
