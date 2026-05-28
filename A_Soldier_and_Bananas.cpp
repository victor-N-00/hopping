#include <iostream>
using namespace std;

int main(){
    int k,n,w;
    cin>>k>>n>>w;
    int actual_cost=k*(w*(w+1)/2);
    if(n<actual_cost){
    int res=abs(n-actual_cost);
    cout<<res;
    }
    else cout<<0;
    return 0;
}