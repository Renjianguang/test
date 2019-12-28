#include <stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
    FILE* fb = fopen("renjg.txt","a");
    if (fb != NULL){
        char str[1024] = "renjianguang";
        fwrite(str,sizeof(char),1024,fb);
        fclose(fb);
        fb = NULL;
    } else {
        printf("error for open file!");
        fb = NULL;
    }
    return 0;
}
