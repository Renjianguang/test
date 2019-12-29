#include <custom_define.h>

int main(void){
    int fd[2];
    char buf[128];
    char *msg = "renjg learn pipe!\n";
    int pp = pipe(fd);
    if(pp == -1)E_MSG("pipe error!",-1);
    pid_t pid = fork();
    if(pid == -1)E_MSG("fork error",-1);
    if(!pid){
        close(fd[1]);
        int r = read(fd[0],buf,128);
        write(1,buf,r);
        close(fd[0]);
        exit(0);
    }else{
        close(fd[0]);
        sleep(5);
        write(fd[1],msg,strlen(msg));
        close(fd[1]);
        wait(NULL);
    }
    return 0;
}
