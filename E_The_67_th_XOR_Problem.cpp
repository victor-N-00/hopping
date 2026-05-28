#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n;cin>>n;
        vector<int>arr(n);
        for(int i=0;i<n;i++){
            cin>>arr[i];
        }
        sort(arr.begin(),arr.end());
    
        while(arr.size()>=1){
            for(int i=0;i<arr.size();i++){
                int can=arr[arr.size()-1];
                arr.erase(arr.end()-1);
                arr[i]=arr[i]^can;
            }
        }
        cout<<arr[0]<<endl;
    }
    return 0;
}