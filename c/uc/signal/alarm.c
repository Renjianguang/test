#include <custom_define.h>

int main(void){
    alarm(5);
    for (int i = 0; i <=250000; i++)
        printf("i = %d\n",i);
    int n = alarm(1);
    printf("n = %d\n",n);
    for (int j = 1; j > 0; j++)
        printf("j = %d\n",j);
    return 0;
}
