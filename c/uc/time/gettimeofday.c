#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main (){
    struct timeval start,end;
    gettimeofday(&start,NULL);
    printf("start time : tv_sec:%ld,tv_usec:%ld\n",start.tv_sec,start.tv_usec);
    sleep(1);
    usleep(600000);
    gettimeofday(&end,NULL);
    printf("end time : tv_sec:%ld,tv_usec:%ld\n",end.tv_sec,end.tv_usec);
    long time;
    time = (end.tv_sec * 1000 + end.tv_usec / 1000)- (start.tv_sec * 1000 + start.tv_usec / 1000);
    printf("time is :%ld\n",time);

    return 0;
}
