#include <iostream>
using namespace std;

int main() {
    cout << "Recurrences Master Theorem Solutions:" << endl;
    cout << "1. T(n) = T(n/2) + n^3 -> O(n^3)" << endl;
    cout << "2. T(n) = 4T(n/3) + n -> O(n^(log3(4)))" << endl;
    cout << "3. T(n) = 4T(n/2) + n -> O(n^2)" << endl;
    cout << "4. T(n) = 3T(n-1) + 1 -> O(3^n)" << endl;
    cout << "5. T(n) = 16T(n/4) + n^2 -> O(n^2 log n)" << endl;
    cout << "6. T(n) = 4T(n/2) + n^2 log n -> O(n^2 log n)" << endl;
    return 0;
}
