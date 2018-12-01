#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>
#include<omp.h>

#define T_COUNT 100000000

double count;

double rnd(){
    return((double)(rand()%RAND_MAX)/(double)RAND_MAX);
}

void* count_points(){
    int i;
    double x,y,co;
    srand(time(NULL));
    #pragma omp parallel for
    for(i=0;i<T_COUNT;i++){
        x=rnd(); y=rnd();
        co=(x*x)+(y*y);
        if(co<=1)
            count++;
    }
    pthread_exit(0);
}

int main(){
    int i;
    double PI,x,y,co=0;
    pthread_t tid;
    pthread_create(&tid,NULL,count_points,NULL);
    pthread_join(tid,NULL);
    PI = 4*(count/T_COUNT);
    printf("Pi:%lf\n",PI);
    return 0;
}

