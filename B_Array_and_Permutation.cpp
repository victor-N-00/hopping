#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;cin>>t;
    while(t--){
        int n;cin>>n;
        vector<int>per(n+1);
        for(int i=1;i<=n;i++){
            int x;cin>>x;
            per[x]=i;
        }

        vector<int>a(n);
        for(auto &x:a) cin>>x;
        
        bool pos=true;
        for(int i=1;i<n;i++){
            if(per[a[i-1]]>per[a[i]]) pos=false;
        }

        cout<<(pos? "YES":"NO")<<endl;
    }
    return 0;
}