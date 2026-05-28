#include <iostream>
#include <vector>
using namespace std;

// Fourier Transform (mod 7)
vector<int> transformMod7(vector<int>& P, int root) {
    int n = P.size();
    vector<int> res(n, 0);
    for (int i = 0; i < n; i++) {
        int power = 1;
        for (int j = 0; j < n; j++) {
            res[i] = (res[i] + P[j] * power) % 7;
            power = (power * root) % 7;
        }
    }
    return res;
}

int main() {
    vector<int> P = {1, 2, 3}; // Poly coefficients
    vector<int> res = transformMod7(P, 2); // 2 is primitive root mod 7
    cout << "Transformed coefficients mod 7: ";
    for (int x : res) cout << x << " ";
    cout << endl;
    return 0;
}
