#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, da, db, t, x;
    cin >> x >> t >> a >> b >> da >> db;
    if (x == 0) {
        cout << "YES\n";
        return 0;
    }

    for (int i = 0; i < t; i++) {
        int p1 = a - i * da;
        if (p1 == x) {
            cout << "YES\n";
            return 0;
        }
    }

    for (int j = 0; j < t; j++) {
        int p2 = b - j * db;
        if (p2 == x) {
            cout << "YES\n";
            return 0;
        }
    }

    for (int i = 0; i < t; i++) {
        for (int j = 0; j < t; j++) {
            int sum = (a - i * da) + (b - j * db);
            if (sum == x) {
                cout << "YES\n";
                return 0;
            }
        }
    }

    cout << "NO\n";
    return 0;
}