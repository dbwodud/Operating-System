#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>

#define MAX_LINE 80

typedef char* string;
typedef struct history{
    char str[80];
    struct history *next;
    struct history *before;
}history;

history* head;
history* cur; 
history* tail;

void init(){
    head = malloc(sizeof(history));
    tail = cur = head;
}

void push_back(string str){
    strcpy(cur->str,str);

}

int main(void){
    
    string args[MAX_LINE/2+1]={NULL,};
    int should_run = 1;
    init();

    while(should_run){
        printf("you>");
        fflush(stdout);
        
        int i=0;
        string original;

        fgets(original,MAX_LINE/2+1,stdin);

        string command = strtok(original," \n");
        if(!command){
            continue;
        }

        if(!strcmp("history",command)){
            continue;
        }
        else if(!strcmp("!!",command)){
            continue;
        }
        else if(!strcmp("!",command)){
            continue;
        }

        while(command){
            args[i++]=command;	
            command = strtok(NULL," \n");
        }
        pid_t pid=fork();
        if(pid<0){
            fprintf(stderr,"Fork Error");
            return 1;
        }
        //Child Process
        else if(!pid){
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
