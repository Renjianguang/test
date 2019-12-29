#include <custom_define.h>
#include <pthread.h>

void* handle(void *arg){
    printf("handle running..\n");
    return ((void*)2);
}
void* handle1(void *arg){
    printf("handle1 running..\n");
    pthread_exit((void*)5);
}
void* handle2(void *arg){
    while(1){
        sleep(1);
        printf("handle2 running..\n");
    }
    return NULL;
}

int main(void){
    pthread_t tid;
    void *ret;
    pthread_create(&tid,NULL,handle,NULL);
    pthread_join(tid,&ret);
    printf("handle exit code...%d\n",(int)ret);
    pthread_create(&tid,NULL,handle1,NULL);
    pthread_join(tid,&ret);
    printf("handle1 exit code...%d\n",(int)ret);
    pthread_create(&tid,NULL,handle2,NULL);
    sleep(4);
    pthread_cancel(tid);
    pthread_join(tid,&ret);
    if(PTHREAD_CANCELED == ret)
        printf("handle2 exit code...%d\n",(int)ret);
    return 0;
}
