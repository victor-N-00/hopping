#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Greedy approach for standard denominations
int greedyCoinChange(vector<int>& coins, int amount) {
    sort(coins.begin(), coins.end(), greater<int>());
    int count = 0;
    for (int coin : coins) {
        if (amount == 0) break;
        count += amount / coin;
        amount %= coin;
    }
    return amount == 0 ? count : -1;
}

int main() {
    vector<int> coins = {25, 10, 5, 1};
    int amount = 67;
    cout << "Coins needed: " << greedyCoinChange(coins, amount) << endl;
    return 0;
}
