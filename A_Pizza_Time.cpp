#include <iostream>
using namespace std;

int main(){
    int t;cin>>t;
    while(t--){
        int n;cin>>n;
        int ans=0;
        while(n>2){
            int m1=n/3,m2=n/3,m3=(n/3)+n%3;
            ans+=m2;
            n=m3;
        }
        cout<<ans<<endl;
    }
    return 0;
}