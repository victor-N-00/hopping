#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int *ptr;

    clock_t T1_st=clock();
    int size=5;
    ptr=malloc(size*sizeof(int));
    for(int i=0;i<size;i++){
        ptr[i]=i+1;
    }
    clock_t T1_sp=clock();

    printf("the elements are:");
    for (int i = 0; i < size; i++)
    {
        printf("%d \t",ptr[i]);
    }

    clock_t T2_st=clock();
    int size2=size+1;
    ptr=realloc(ptr,size2*sizeof(int));
     for(int i=0;i<size2;i++){
        ptr[i]=i+1;
    }
    clock_t T2_sp=clock();
    printf("\nthe elements in new size are:");
    for (int i = 0; i < size2; i++)
    {
        printf("%d \t",ptr[i]);
    }
    double t1= (double) (T1_st-T1_sp)/CLOCKS_PER_SEC;
    double t2= (double) (T2_st-T2_sp)/CLOCKS_PER_SEC;
    printf("\n%f \n %f \n",t1,t2);
    return 0;
}
