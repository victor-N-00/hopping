#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n+1), b(n+1), p(n+1);

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    // core logic
    for (int i = 1; i <= n; i++) {
        p[a[i]] = b[i];
    }

    for (int i = 1; i <= n; i++) {
        cout << p[i] << " ";
    }
}