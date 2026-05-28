#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    int cx = 0, cy = 0;

    for (char c : s) {
        if (c == 'x') cx++;
        else cy++;
    }

    if (cx > cy) {
        cout << string(cx - cy, 'x') << "\n";
    } else {
        cout << string(cy - cx, 'y') << "\n";
    }

    return 0;
}