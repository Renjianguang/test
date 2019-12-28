#include <stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
    FILE* fb = fopen("renjg.txt","r");
    if (fb != NULL){
        char str[1024] = {0};
        fread(str,sizeof(char),1024,fb);
        fclose(fb);
        fb = NULL;
        printf("%s\n",str);
    } else {
        printf("error for open file!");
        fb = NULL;
    }
    return 0;
}
