#include<sys/wait.h>
#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>

int main(){
    int n;
    pid_t pid;
    printf("Enter N:");
    scanf("%d",&n);
    pid = fork();
 
    
    if(pid<0){
        fprintf(stderr,"Can't Fork");
        return 1;
    }
    //Child
    else if(pid==0){
        while(n>1){
            printf("%d, ",n);
            if(n%2==0) n = n/2;
            else n = 3*n + 1;
        }
        printf("%d\n",n);
    }
    //Parent
    else{
        wait(NULL);
    }
    return 0;
}
