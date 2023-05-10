#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char*argv[]){
    int sizestr=0;//макс размер строки
    double tmp, s=0;
    char* end=NULL;
    for (int i=1; i<argc; i++)
        sizestr+=strlen(argv[i])+1;//находим максимальную длинну строки чтобы выделить память
    char* resstr=(char*)malloc(2*sizestr);//выделение памяти в 2 раза больше
    char* tmps=resstr;
    for (int i=1; i<argc; i++){
        if (((tmp=strtod(argv[i], &end))!=0)&&(*end=='\0'))
            s+=tmp;
        else if(*end!='\0'){
            strcpy(tmps, argv[i]);
            tmps+=strlen(argv[i]);
        }
    }
    strcpy(tmps, resstr);
    printf("%lf\n", s);
    printf("%s\n", resstr);
    return 0;
}
