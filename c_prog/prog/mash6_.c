#include <stdio.h>

int main(int argc, char **argv)
{
    FILE *F;
    int count = 0;
    char prev, now;
    if ((F = fopen(argv[argc - 1], "r+")) == NULL)
    {
        printf("ERROR");
        return 1;
    }
    while ((prev = fgetc(F)) != EOF)
    {
        now = prev;
        if (prev == '\n')
        {
            count++;
        }
    }
    if (now != '\n')
    {
        count++;
        fputc('\n', F);
    }

    printf("%d\n", count);
    return 0;
}