#include <iostream>
#include <vector>
using namespace std;

int main(){
    int x,y;
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            int k;
            cin>>k;
            if(k==1){
                x=i+1;y=j+1;
                break;
            }
        }
    }

    int res=abs(3-x)+abs(3-y);
    cout<<res;
    return 0;
}