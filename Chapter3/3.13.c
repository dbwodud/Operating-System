#define MIN_PID 300
#define MAX_PID 5000

int allocate_map(void);
int allocate_pid(void);
void release_pid(int pid);

int pid_map[4700];

int allocate_map(){
    int i=0;
    for(;i<MAX_PID;i++){
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
