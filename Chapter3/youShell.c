#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>

#define MAX_LINE 80
int main(void){
    char *args[MAX_LINE/2+1]={NULL};
    int should_run = 1;

    while(should_run){
        printf("you>");
        fflush(stdout);
        int i;
        char *original;
        fgets(original,MAX_LINE/2+1,stdin);
        char *command = strtok(original," ");
        i=0;
        while(command!=NULL){
            args[i++]=command;	
            command = strtok(NULL," ");
        }
        pid_t pid;
        pid = fork();
        if(pid<0){
            fprintf(stderr,"Fork Error");
            return 1;
        }
        //Child Process
        else if(pid==0){
            printf("%s",args[0]);
            if(args[1]==NULL){
                printf("NULL");
            }
            execvp(args[0],args);
            printf("command is not valid\n");
        }
        //Parent Process
        else{
            wait(NULL);
        }
    }
    return 0;
}
