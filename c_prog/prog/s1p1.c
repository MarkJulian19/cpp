#include <stdio.h>
#include <stdlib.h>
#define block_size 4
char *str_read(char *str){
    int len =1;
    char c;
    while(((c = getchar()) != '\n')&&(c!= EOF)) {
        str[len - 1] = c;
        if ((len % block_size) == 0){
            str = (char*)realloc(str,len+block_size);
        }
        len++;
    }
    printf("%d",len);
    str[len-1] = '\0';
    return str;
}

int main()
{
    char *strochka = (char *)calloc(block_size, sizeof(char));
    strochka = str_read(strochka);
    printf("\n");
    printf("%s\n", strochka);
    free(strochka);
    return 0;
}
