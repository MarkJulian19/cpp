#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int str_read(char *stra,char *strb, char buk){
	char *tmpa=stra;
	char *enda;
	char *tmpb=strb;
	char *word;
	int counter = 0;
	if (tmpa == NULL){
		strb = NULL;
		printf("This pointer is NULL\n");
		return 0;
	}
	while (*tmpa != '\0'){
		if (*tmpa != ' '){
			enda = tmpa;
			while ((*enda != ' ') && (*enda != '\0')){
				if (*enda == buk) counter = 1;
				enda++;
			}
			if (counter){
				strncpy(tmpb, tmpa, enda - tmpa + 1);
				tmpb += enda - tmpa + 1;
				counter = 0;
			}
		tmpa = enda-1;	
		}
	tmpa++;
	}
	return 0;	
}

int main(){
	char *str=(char*)malloc(256);
	char *str2=(char*)malloc(256);
	char bukwa;
	printf("Введите параметр: ");
	scanf("%c",&bukwa);
	printf("Введите строку:");
	scanf("\n%[^\n]s",str);
	printf("%s\n",str);
	printf("%c\n",bukwa);
    	str_read(str, str2,bukwa);
	printf("%s\n",str2);
	str = NULL;
	str_read(str,str2,bukwa);	
	return 0;
}
