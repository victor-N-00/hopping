#include <iostream>
#include <vector>
using namespace std;

int evaluatePolynomial(vector<int>& coeffs, int x) {
    int result = 0;
    for (int i = coeffs.size() - 1; i >= 0; i--) {
        result = result * x + coeffs[i];
    }
    return result;
}

int main() {
    vector<int> coeffs = {2, -6, 2, -1}; // -x^3 + 2x^2 - 6x + 2
    int x = 3;
    cout << "Evaluation at x=" << x << ": " << evaluatePolynomial(coeffs, x) << endl;
    return 0;
}
