#include <custom_define.h>

int main(int argc,char *argv[]){
    char *msg = "mkfifo success!\n";
    int ff=mkfifo(argv[1],0644);
    if(ff == -1)E_MSG("mkfifo",-1);
    write(1,msg,strlen(msg));
    return 0;
}
