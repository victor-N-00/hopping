#include <stdio.h>
#include <math.h>
#include <time.h>

void f1(int n){
 if(n<=1)return;
 
 int sz=n*log(n);
 double c=0.00;
 for(int i=0;i<sz;i++){c++;}
 f1(n/2); 
 f1(n/2);
}

int main(){
int ar[]={500,1000,2000,4000,8000};
int size=5;
for(int i=0;i<size;i++){
        int num=ar[i];
        clock_t st=clock();
        f1(num);
        clock_t sp=clock();
        double t =(double)(sp-st)/CLOCKS_PER_SEC;
        printf("%-15d | %lf \n",num,t);
     }
       
  return 0;
}
