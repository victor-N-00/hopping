#include<iostream>
#include <iomanip>
#include<vector>
using namespace std;

int main(){

int n;
cin >> n;

double sum = 0;
for (int i = 0; i < n; i++) {
    double x;
    cin >> x;
    sum += x;
}

double res = sum / n;
cout << fixed << setprecision(12) << res;
}