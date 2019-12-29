#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#define E_MSG(msg,error) do{printf("%s\n",msg);return error;}while(0);
int main(int argc,char *argv[]){
    DIR *dir = opendir(argv[1]);
    if (!dir)E_MSG("opendirerror",-1);
    //E_MSG("success",0);
    while(1){
        struct dirent *p = readdir(dir);
        if(!p)break;
        printf("file:%s\tinode:%lu\n",p->d_name,p->d_ino);
    }
    closedir(dir);
    return 0;
}
