#include <iostream>
#include <cmath>
using namespace std;

bool isPowerForm(int n) {
    if (n <= 1) return true;
    for (int b = 2; b <= sqrt(n); b++) {
        int p = b;
        while (p <= n / b) {
            p *= b;
            if (p == n) return true;
        }
    }
    return false;
}

int main() {
    int n = 81; // 3^4
    cout << n << " is power form: " << (isPowerForm(n) ? "Yes" : "No") << endl;
    return 0;
}
