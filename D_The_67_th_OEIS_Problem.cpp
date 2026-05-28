#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAX = 200000;
    vector<bool> is_prime(MAX, true);
    vector<long long> primes;

    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i < MAX; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (long long j = 1LL * i * i; j < MAX; j += i)
                is_prime[j] = false;
        }
    }

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << primes[i] * primes[i + 1] << " ";
        }
        cout << '\n';
    }

    return 0;
}