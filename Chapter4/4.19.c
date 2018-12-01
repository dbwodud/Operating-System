#include<pthread.h>
#include<stdio.h>

int n;

void* print_prime_number(){
    int i,j;
    for(i=1;i<=n;i++){
        for(j=2;j<i;j++){
            if(i%j == 0)
                break;
        }
        if(j==i)
            printf("%d\t",i);
    }
    pthread_exit(0);
}
int main(){
    int i,j;
    scanf("%d",&n);
    pthread_t tid;
    pthread_create(&tid,NULL,print_prime_number,NULL);
    pthread_join(tid,NULL);

    return 0;
}
