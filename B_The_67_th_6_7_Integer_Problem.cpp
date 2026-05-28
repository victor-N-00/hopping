#include <iostream>
#include <limits.h>
#include <vector>
using namespace std;

int main(){
    int t;cin>>t;
    while(t--){
        int total_sum=0;
        vector<int>arr(7);
        for(int i=0;i<7;i++){
            cin>>arr[i];
            total_sum+=arr[i];
        }
        total_sum*=-1;
        int res=INT_MIN,sum=0;
        for(int i=0;i<arr.size();i++){
            sum=2*arr[i]+total_sum;
            res=max(sum,res);
        }
        cout<<res<<endl;
    }
    return 0;
}