#include <iostream>
#include <string>
using namespace std;

int main(){
    int n,t;
    cin>>n>>t;
    string s;
    cin>>s;

    for(int i=0;i<t;i++){
        for(int j=1;j<s.size();j++){
            if(s[j-1]=='B'&&s[j]=='G'){
                swap(s[j],s[j-1]);
                j++;
            }
        }
    }
    cout<<s;
    return 0;
}