#include <iostream>
using namespace std;

int main(){
    int t;cin>>t;
    while(t--){
        int n;cin>>n;
        int ans=0,n1=0;
        for(int i=0;i<n;i++){
            int x;cin>>x;
            if(x==0){
                ans++;
            }if(x==-1){
                n1++;
            }
        }

        if(n1%2!=0){ans+=2;}
        
        cout<<ans<<endl;
    }
    return 0;
}