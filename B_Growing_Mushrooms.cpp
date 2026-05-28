#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,t1,t2,k;
    cin>>n>>t1>>t2>>k;
    
    double x= t1*(1-k/100.0);
    double y= t2;

    vector<pair<int,double>>res;
    for(int i=0;i<n;i++){
        int a,b; cin>>a>>b;
        double res1=a*x+b*y;
        double res2=b*x+a*y;
        res.push_back({i+1,max(res1,res2)});
    }
    sort(res.begin(), res.end(), [](auto &a, auto &b){
    if (abs(a.second - b.second) > 1e-9)
        return a.second > b.second;   
        return a.first < b.first;}); 
    cout << fixed << setprecision(2);
    for (auto &p : res) {
        cout << p.first << " " << p.second << "\n";
    }
    return 0;
}