#include <custom_define.h>

int main(void){
    char *ls_argv[] = {"ls","-al",NULL};
    pid_t pid = fork();
    if(pid == -1)E_MSG("fork error",-1);
    if(pid == 0){
        execvp("ls",ls_argv);
        perror("execl");
        exit(-1);
    }else{
        wait(NULL);
    }

    return 0;
}
