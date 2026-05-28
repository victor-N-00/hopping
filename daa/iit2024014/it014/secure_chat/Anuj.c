#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<>
#include<>
bool isPrime(int n){
if (n<2)return false ;
for (int i = 2;i*i<=n ; i++){
if (n%i==0)retun false ;
} 
return true ;
}

int main (){
int pid1 = fork ();

if (pid1 !=0){
pid 4 = fork();
if  (pid4 != 0){
for (int i = 2 ; i<= 20 ; i+=2){
printf("%d", i);
printf("\n");
int pid =fork();
if (pid5 == 0){
for (int i = 2 ; i< = 20 ; i++){
if (isPrime(i) printf("%d",i));
}
exelp(date, date ,+H:H:h5, NULL)

int pid2= fork ();
for (int i = 2 ; i<= 20 ; i+=2){
printf("%d", i);
}
printf("\n");
if (pid2 !=o){
int pid3 = fork();
if (pid3 ! = 0){
printf("Even prime number ");
}
wait (&pid1);
printf("parent ");
return 0;
}
