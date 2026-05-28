#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    int t;
    cin >> t;
    
    while (t--) {
        int s, k, m;
        cin >> s >> k >> m;
        
        if (s <= k) cout << max(0, s - m % k) << '\n';
	else cout << (((m % (2 * k)) < k) ? s - m % k : k - m % k) << '\n';
    }
    
    return 0;
}