#include <stdio.h>
int main(){
    FILE *fb = fopen("renjg.txt","a");
    if (fb){
        char str[1024] = "memba";
        int val = 66666;
        fprintf(fb," add for %s %d\n",str,val);
        fclose(fb);
        fb = NULL;
    }
    return 0;
}
