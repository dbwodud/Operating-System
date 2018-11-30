#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>

#define END 7
#define NTHREAD 3

int arr[END];

void* get_max(){
    int max;
    int i;
    for(i=0;i<END;i++){
        if(i==0){
            max = arr[i];
            continue;
        }
        else{
            if(arr[i]>max){
                max = arr[i];
            }
        }
    }
    printf("The maximum value is %d\n",max);
    pthread_exit(0);
}

void* get_min(){
    int min;
    int i;
    for(i=0;i<END;i++){
        if(i==0){
            min = arr[i];
        }
        else{
            if(arr[i]<min){
                min = arr[i];
            }
        }
    }
    printf("The minimum value is %d\n",min);
    pthread_exit(0);
}

void* get_avg(){
    int avg;
    int i,sum=0;
    for(i=0;i<END;i++){
        sum+=arr[i];
    }
    avg = sum/END;
    printf("The average value is %d\n",avg);
    pthread_exit(0);
}

int main(){
pid_t pid;
pthread_t tid[NTHREAD];
pthread_attr_t attr[NTHREAD];

    int i;
    
    for(i=0;i<7;i++){
        scanf("%d",&arr[i]);
    }
    for(i=0;i<7;i++)
        printf("%d\n",arr[i]);

    pid = fork();

    if(pid<0){
        fprintf(stderr,"Make Child Process Failed");
        exit(1);
    }
    //Child Process
    if(pid==0){
        pthread_create(&tid[0],NULL,get_avg,NULL);
        pthread_create(&tid[1],NULL,get_min,NULL);
        pthread_create(&tid[2],NULL,get_max,NULL);

        for(i=0;i<NTHREAD;i++)
            pthread_join(tid[i],NULL);
    }
    else if(pid>0){
        wait(NULL);
    }
    return 0;
}
