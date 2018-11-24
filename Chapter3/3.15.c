#include<sys/types.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(){
    const int SIZE = 8192;
    const char *name = "OS";

    int n;
    int shm_fd;
    int *ptr;
    printf("input N : ");
    scanf("%d",&n);
    
    shm_fd = shm_open(name,O_CREAT|O_RDWR,0666);
    ftruncate(shm_fd,SIZE);

    pid_t pid;
    pid = fork();


    if(pid<0){
        fprintf(stderr,"Fork Errored");
        return 1;
    }
    //Child Process
    else if(pid==0){
        ptr = (int *)mmap(0,SIZE,PROT_WRITE,MAP_SHARED,shm_fd,0);
        int i=0;
        while(n>1){
            ptr[i++]=n;
            if(n%2==0)n=n/2;
            else n = 3*n + 1;
        }
        ptr[i]=n;
    }
    // Parent Process
    else{
        wait(NULL);
        ptr = mmap(0,SIZE,PROT_READ,MAP_SHARED,shm_fd,0);
        int i=0;
        while(ptr[i]!=1){
            printf("%d,",ptr[i++]);
        }
        printf("%d\n",ptr[i]);
    }

    return 0;
}
