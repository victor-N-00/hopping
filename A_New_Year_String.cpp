#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;cin>>n;
        string s;cin >> s;

        bool has2025 = false, has2026 = false;

        for (int i = 0; i + 3 < (int)s.size(); i++) {
            string sub = s.substr(i, 4);
            if (sub == "2025") has2025 = true;
            if (sub == "2026") has2026 = true;
        }

        if (has2025 && !has2026)
            cout << 1 << '\n';
        else
            cout << 0 << '\n';
    }

    return 0;
}