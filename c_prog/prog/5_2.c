#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int f_str(FILE *f, char *s)
{
    char c;
    int state = 0;
    while (((c = fgetc(f)) != '\n') && (c != EOF))
        if (c == *s)
            state = 1;
    if (state)
        return ftell(f);
    else
        return 0;
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Error args\n");
        return 1;
    }
    FILE *F;
    if (F = fopen(argv[1], "r"))
    {
        fseek(F, 0, SEEK_END);
        int size = ftell(F) + 1;
        long int curpos = 0, endstr = 0;
        int i, pend;
        char *Data = malloc(sizeof(char) * size);
        char *ptr = Data;
        *ptr = 0;
        fseek(F, 0, SEEK_END);
        pend = ftell(F);
        fseek(F, 0, SEEK_SET);
        while (ftell(F) != pend)
        {
            curpos = ftell(F);
            if (f_str(F, argv[2]) == 0)
            {
                endstr = ftell(F);
                fseek(F, curpos, SEEK_SET);
                fgets(ptr, endstr - curpos + 1, F);
                ptr += endstr - curpos;
            }
        }
        fclose(F);
        F = fopen(argv[1], "w");
        fputs(Data, F);
        fclose(F);
        free(Data);
    }
    return 0;
}