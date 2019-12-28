#include<stdio.h>

int main(){
    FILE *fb = fopen("renjg.txt","r");
    if (fb){
        char str[1024] = {0};
        fscanf(fb,"%s",str);
        fclose(fb);
        fb = NULL;
        printf("%s\n",str);
    }
    return 0;
}
