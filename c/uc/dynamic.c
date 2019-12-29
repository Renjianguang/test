#include <stdio.h>
#include <dlfcn.h>
int main(int argc , char *argv[]){
    int (*func)(const char* name);
    void *p = dlopen(argv[1],RTLD_LAZY);
    if(p){
       void *f = dlsym(p,"print_name");
       if(f){
        func = f;
        func("renjg");
       }
       dlclose(p);
    } else {
        printf("dlopen faile!!");
    }
    return 0;
}
