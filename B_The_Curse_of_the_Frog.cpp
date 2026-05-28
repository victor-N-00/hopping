#include <bits/stdc++.h>
using namespace std;

#define int long long
#define all(a) a.begin(), a.end()
#define rall(a), a.rbegin(), a.rend()

const int mod = 1e9+7;
const int inf = 1e9;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i] >> c[i];
    }
    int start = 0;
    int mx = -inf;
    for (int i = 0; i < n; ++i) {
        mx = max(mx, a[i] * b[i] - c[i]);
        start += a[i] * (b[i] - 1);
    }
    x -= start;
    if (x <= 0) {
        cout << 0;
        return; 
    }
    if (mx <= 0) {
        cout << -1;
        return;
    }
    cout << (x + mx - 1) / mx;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    cin >> tt;
    while (tt--) {
        solve();
        cout << '\n';
    }
}