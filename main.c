#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void copy(char *, char *);
int main(){
    char c[50] = "hello";
    char c1[50];
    copy(c1, c);
    printf("%s  ", c1);
    return 0;
}

void copy(char* c1, char*c){
    strcpy(c1, c);
}