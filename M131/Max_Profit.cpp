#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxProfit(vector<int>& prices) {
    int min_price = 1e9, max_prof = 0;
    for (int p : prices) {
        min_price = min(min_price, p);
        max_prof = max(max_prof, p - min_price);
    }
    return max_prof;
}

int main() {
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << "Max Profit: " << maxProfit(prices) << endl;
    return 0;
}
