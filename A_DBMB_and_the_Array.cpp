#include<iostream>
#include<vector>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n,s,x;
        int sum=0;
        cin>>n>>s>>x;
        vector<int>nums(n);
        for(int i=0;i<n;i++){
            cin>>nums[i];
            sum+=nums[i];
        }

        // sum+c.x=s  => c=s-sum/x =>if c is not  a perfect int =>no; 
        
        int numerator = s - sum;
        if (x != 0 && numerator % x == 0 && numerator>=0) {
            int c = numerator / x;
            cout<<"YES"<<endl;
        } else {
            cout<<"NO"<<endl;
        }

    }
    return 0;
}