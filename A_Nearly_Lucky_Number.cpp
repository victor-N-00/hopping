#include <iostream>
using namespace std;

int main(){
    long long int num;
    cin >> num;
    
    int res=0;
    while(num>0){
        int rem=num%10;
        num/=10;
        if(rem==4){res++;}
        if(rem==7){res++;}
    }
    if(res==4 || res==7){cout<<"YES";}
    else cout<<"NO";
    return 0;
}