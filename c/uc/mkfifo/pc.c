#include <custom_define.h>

int main(int argc,char *argv[]){
    char *msg = "pc write pb read!\n";
    int fd = open(argv[1],O_WRONLY);
    if(fd == -1)E_MSG("open fail!\n",-1);
    write(fd,msg,strlen(msg));
    close(fd);
    return 0;
}
