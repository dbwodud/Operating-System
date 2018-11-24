#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
    pid_t pid,pid1;

    pid = fork();

    if(pid<0){ // Fork Failed
        fprintf(stderr,"Fork Failed");
        return 1;
    }
    else if(pid==0){ // Child process
        pid1=getpid();
        printf("child: pid = %d\n",pid);
        printf("child: pid1 = %d\n",pid1);
    }
    else{ // Parent process
        pid1 = getpid();
        printf("parent : pid = %d\n",pid);
        printf("parent : pid1 = %d\n",pid1);
        wait(NULL);
    }

    return 0;
}
