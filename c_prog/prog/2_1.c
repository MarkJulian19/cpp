#include <stdio.h>
#include <stdlib.h>
unsigned int str_len(const char *str){
    return (*str) ? str_len(++str) + 1 : 0;
}
char *last(char *s1, char *s2){
    if (s1 == NULL){
        printf("Изначально пустая строка\n");
        return NULL;
    }
    int L1= str_len(s1);
    int L2= str_len(s2);
    for(int i=L1-L2;i>=0;i--){
        int j=0;
        for(;j<L2;j++)
            if(s1[i+j]!=s2[j])
                break;
        if(j==L2)
            return s1+i;
    }
    printf("Не найдено ни одного вхождения подстроки\n");
    return NULL;
}

int main(){
    char *str=(char*)malloc(256);
	char *str2=(char*)malloc(256);
    char *str3;
    scanf("\n%[^\n]s",str);
    scanf("\n%[^\n]s",str2);
    printf("%s\n", str);
    printf("%s\n", str2);
    str3 = last(str,str2);
    if (str3!=NULL)
        printf("%s\n", str3);
    else
        printf("Пустая строка\n");
    return 0;
}