#include<custom_define.h>
#include<signal.h>

void handle(int n){
    printf("n is %d",n);
    return;
}

int main(void){
    signal(3,handle);
    while(1);
    return 0;
}
