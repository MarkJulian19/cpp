#include <stdio.h>
#include <stdlib.h>
int *strcounter(FILE *f){
    char c,tmp;
    int count=0, str_num=0, *strinfo=malloc(sizeof(int));
    while((c=fgetc(f))!=EOF) {
        tmp=c;
        str_num++;
        if (c=='\n'){
            strinfo[count]=str_num;
            strinfo=realloc(strinfo, count+1);
            count++;
        }
    }
    if (tmp!='\n') {
        strinfo[count]=str_num;
        strinfo=realloc(strinfo, count+1);
        count++;
        fputc('\n',f);
    }
    return strinfo;
}

int main(int argc, char**argv){
    FILE *f;
    char str[100];
    int input=0, i, sizemas;
    if((f=fopen(argv[argc-1], "r+"))==NULL){
        printf("MISS");
        return 1;
    }
    int *str_val=strcounter(f);
    sizemas=sizeof(str_val)/sizeof(int)+1;
    //printf("%d\n",sizemas);
    scanf("%d",&i);
    while(i!=0){
        if(i>sizemas+1) {
            printf("ERROR. Введите другой номер строки\n");
            scanf("%d",&i);
            continue;
        }
        if (i==1) fseek(f, 0L, SEEK_SET);
        else fseek(f, str_val[i-2], SEEK_SET);
        fgets(str,100,f);
        printf("%d-я строка: %s",i, str);
        scanf("%d",&i);
    }
    fclose(f);
    return 0;
}