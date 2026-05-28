#include <iostream>
#include <cmath>
using namespace std;

// Alternate exponential search
int findTreasure(int position) {
    int step = 1;
    int current = 0;
    while (true) {
        // Check range [current, current + step] or similar
        // Simplification for representation
        if (abs(position) <= step) return step;
        step *= -2; // Alternate sign and double
    }
    return -1;
}

int main() {
    cout << "Treasure Hunt Search Strategy (Exponential)." << endl;
    return 0;
}
