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
    struct history *llink;
    struct history *rlink;
}history;

history* head;
history* cur; 
history* tail;
int n=0;

history* create(string str){
    n++;
    history* new_node;
    new_node = (history*)malloc(sizeof(history));
    strcpy(new_node->str,str);
    new_node->rlink = NULL;
    new_node->llink = NULL;
    return new_node;
}

void push_back(string str){
    if(!head){
        head = create(str);
        tail = head;
    }
    else{
        history* temp = create(str);
        tail -> rlink = temp;
        temp -> llink = tail;
        temp -> rlink = NULL;
        tail = temp;
    }
}

void init(){
    head = NULL;
    tail = NULL;
    cur = NULL;
}

int main(void){
    string args[MAX_LINE/2+1]={NULL,};
    int should_run = 1;
    
    init();

    while(should_run){
        printf("you>");
        fflush(stdout);
        
        int i=0;
        char original[80];
        char temp[80];
        fgets(original,MAX_LINE/2+1,stdin);
        strcpy(temp,original);
        string command = strtok(temp," \n");
        if(!command)
            continue;
        if(!strcmp("history",command)){
            cur = tail;
            int x = n;
            while(cur){
                printf("%d %s",x,cur->str);
                cur=cur->llink;
                x--;
            }
            continue;
        }
        else if(!strcmp("!!",command)){
            printf("%s\n",tail->str);
            continue;
        }
        else if(!strcmp("!",command)){
            continue;
        }
        push_back(original);
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
