#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc == 1)
        return 0;
    FILE *F[argc];
    int flageof[argc], num[argc], i, count = 0;
    for (i = 1; i < argc; i++)
    {
        F[i] = fopen(argv[i], "r");
    }
    for (i = 1; i < argc; i++)
    {
        if (fscanf(F[i], "%d", &num[i]) == 1)
        {
            //printf("%d", num[i]);
            count++;
            flageof[i] = 1;
        }
        else
            flageof[i] = 0;
    }
    int min, minj = 0;
    while (count > 0)
    {
        min = __INT_MAX__;
        for (i = 1; i < argc; i++)
        {
            if (flageof[i] != 0)
            {
                if (num[i] <= min)
                {
                    min = num[i];
                    minj = i;
                }
            }
        }
        printf("%d ", min);
        if (fscanf(F[minj], "%d", &num[minj]) != 1)
        {
            flageof[minj] = 0;
            count--;
        }
    }
    printf("\n");
    for (i = 1; i < argc; i++)
    {
        fclose(F[i]);
    }
    return 0;
}