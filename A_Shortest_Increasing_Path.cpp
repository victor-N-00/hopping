#include <iostream>
using namespace std;

int main(){
    int t;
	cin>>t;
	while(t--){
		int x,y;
		cin>>x>>y;
		if(x==y || x==y+1 || y==1)cout<<-1<<endl;
		else if(x<y)cout<<2<<endl;
		else cout<<3<<endl;
    }
    return 0;
}



