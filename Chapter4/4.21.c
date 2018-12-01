#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>


#define INT 8

int n;
int *arr;

int fib(int n){
    if(n<=1){
        arr[n]=n;
        return n;
    }
    else{
        arr[n]=fib(n-1)+fib(n-2);
        return fib(n-1)+fib(n-2);
    }
}


void* fib_start(){
    fib(n);
    pthread_exit(0);
}

int main(){
    scanf("%d",&n);
    arr = malloc(INT*n);
    pthread_t tid;
    pthread_create(&tid,NULL,fib_start,NULL);
    pthread_join(tid,NULL);
    int i;
    for(i=0;i<n;i++){
        printf("%d\t",arr[i]);
    }
    printf("\n");

    return 0;
}
