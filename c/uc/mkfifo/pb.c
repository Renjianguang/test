#include <custom_define.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc,char *argv[]){
    char buf[128];
    int fd = open(argv[1],O_RDONLY);
    if(fd == -1)E_MSG("open fail!",-1);
    int r = read(fd,buf,128);
    write(1,buf,r);
    close(fd);
    return 0;
}
