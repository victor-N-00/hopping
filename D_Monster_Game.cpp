#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
const int N = 2e5 + 12;
 
int t, n, a[N], b[N];
 
int main()
{
    cin >> t;
    
    while( t -- )
    {
        cin >> n;
        
        for( int i = 1; i <= n; i ++ ) cin >> a[i];
        for( int i = 1; i <= n; i ++ ) cin >> b[i];
        
        int j = 0, sum = 0; ll ans = 0;
        sort(a + 1, a + n + 1); reverse(a + 1, a + n + 1);
        
        for( int i = 1; i <= n; i ++ )
        {
            while( j < n && sum + b[j + 1] <= i ) j ++, sum += b[j];
            ans = max(ans, a[i] * 1ll * j);
        }
        cout << ans << '\n';
    }
}