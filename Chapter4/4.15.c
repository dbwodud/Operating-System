#include<pthread.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define MIN_PID 300
#define MAX_PID 5000
#define NTHREADS 50

void* runner();
void* runner2();
int allocate_map(void);
int allocate_pid(void);
void release_pid(int pid);

int i;

int pid_map[4700];

int main(){
    pthread_t tid[NTHREADS];
    pthread_attr_t attr;

    allocate_map();
    srand(time(NULL));
    pthread_attr_init(&attr);
    
    int j;
    for(j=0;j<NTHREADS;j++){
        printf("%d\n",j);
        if(!(j%2))
            pthread_create(&tid[j],&attr,runner,NULL);
        else
            pthread_create(&tid[j],&attr,runner2,NULL);
    }
    for(j=0;j<NTHREADS;j++){
        pthread_join(tid[j],NULL);
    }

    return 0;
}
int allocate_map(){
    int i;
    for(i=0;i<MAX_PID;i++){
        pid_map[i]=0;
    }
    return 1;
}

int allocate_pid(){
    int i;
    for(i=0;i<MAX_PID;i++){
        if(!pid_map[i]){
            pid_map[i]=1;
            return i+MIN_PID;
        }
    }
}

void release_pid(int pid){
    pid_map[MIN_PID+pid]=0;
}

void *runner(){
    int pid = allocate_pid();
    printf("Acquired pid = %d\n",pid);

    int sec = rand()%10;
    printf("Sleeping for %d secs\n",sec);
    sleep(sec);

    printf("Released pid = %d\n",pid);
    pthread_exit(0);
}

void *runner2(){
    int pid = allocate_pid();
    printf("Acquired pid1 = %d\n",pid);

    int sec = rand() % 10;
    printf("Sleeping for %d secs\n",sec);
    sleep(sec);

    printf("Released pid1 = %d\n",pid);
    pthread_exit(0);
}
