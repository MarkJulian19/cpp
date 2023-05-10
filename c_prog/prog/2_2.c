#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int str_len(const char *str){
    return (*str) ? str_len(++str) + 1 : 0;
}

char *last(char *s1, char *s2){
    if (s1 == NULL){
        //printf("Изначально пустая строка\n");
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
    //printf("Не найдено ни одного вхождения подстроки\n");
    return NULL;
}

char* change_str(char *s1, char *s2){
    char *Joseph_Joestar;
    int Ls1 = str_len(s1), Ls2 = str_len(s2);
    if ((Ls1<=0) || (Ls2<=0) || (Ls1<Ls2)){
        printf("Введены некорректные изначальные данные");
        return NULL;
    }
    while((Joseph_Joestar = last(s1,s2)) != NULL){
        strcpy(Joseph_Joestar, Joseph_Joestar + Ls2);
    }
}


int main()
{
    char *str=(char*)malloc(256);
	char *str2=(char*)malloc(256);
    scanf("\n%[^\n]s",str);
    scanf("\n%[^\n]s",str2);
    printf("%s\n", str);
    printf("%s\n", str2);
    change_str(str, str2);
    printf("%s\n", str);
    free(str);
    free(str2);
    return 0;
}