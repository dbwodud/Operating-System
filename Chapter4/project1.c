#include<pthread.h>
#include<stdio.h>

typedef struct{
    int row;
    int column;
}parameters;

void* check_column(){


}
void* check_row(){

}
void* subgirds(){

}

int main(){
    parameters* data = (parameters *)malloc(sizeof(parameters));
    data->row = 1;
    data->column = 1;

    return 0;
}
