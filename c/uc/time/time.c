#include <time.h>
#include <unistd.h>
#include <stdio.h>
int main(){
    time_t start,end;
    start = time(NULL);
    printf("start timme:%ld\n",start);
    sleep(1);
    end = time(NULL);
    printf("end timme:%ld, start-end= %ld\n",end,end - start);
    return 0;
}
