#include<pthread.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>

int value=0;
void *runner(void *param);

int main(int argc,char *argv[]){
pid_t pid;
pthread_t tid;
pthread_attr_t attr;

    pid = fork();

    if(!pid){ // Child Process
        pthread_attr_init(&attr);
        pthread_create(&tid,&attr,runner,NULL);
        pthread_join(tid,NULL);
        printf("CHILD : value = %d",value); 
    }
    else if(pid>0){
        wait(NULL);
        printf("PARENT : value = %d",value); /* LINE P */
    }
    return 0;
}

void *runner(void *param){
    value = 5;
    pthread_exit(0);
}
