#include<sys/types.h>
#include<sys/wait.h>

#include<stdio.h>
#include<unistd.h>

#define MAX_LINE 80

int main(void){
    char *args[MAX_LINE/2+1];
    int should_run = 1;

    while(should_run){
        printf("you>");
        fflush(stdout);
        pid_t pid;
        pid = fork();
        if(pid<0){
            fprintf(stderr,"Fork Error");
            return 1;
        }
        //Child Process
        else if(pid==0){
            execvp(args[0],args);
        }
        //Parent Process
        else{

            wait(NULL);
        }
    }
    return 0;
}
