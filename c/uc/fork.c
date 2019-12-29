#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <custom_define.h>
int main(int argc, char *argv[]){
    pid_t pid = fork();
    if(pid == -1)E_MSG("forkerror",-1);
    if(pid == 0){
        printf("child process...%d\n",getpid());
        printf("parent pid in child process...%d\n",getppid());
    } else{
        printf("parent process...%d\n",getpid());
        printf("parent pid in parent process...%d\n",getppid());
    }
    getchar();
    return 0;
}
