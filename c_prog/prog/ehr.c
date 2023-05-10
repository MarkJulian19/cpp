#include <stdio.h>
#include <stdlib.h>

#define maxlen 4

void print(char *str)
{
    int i = 0;

    char c = str[i];

    while (c != '\0')
    {
        putchar(c);
        i += 1;
        c = str[i];
    }

    printf("\n");

    return;
}

void exchange(char *str)
{

    if (str == NULL)
        return;

    int i = 0, k = 0; // k ввел для позиции последнего плюса в строке

    char c = str[i];

    char *s1 = (char *)malloc(maxlen * sizeof(char));

    while (c != '+' && c != '\0')
    {
        if ((i + 1) % 4 == 0)
            s1 = (char *)realloc(s1, (i + maxlen) * sizeof(char));
        s1[i] = c;
        i += 1;
        c = str[i];
    }

    int L1 = i;

    if (c == '\0')
    {
        free(s1);
        print(str);
        return;
    }

    while (c != '\0')
    {
        if (c == '+')
            k = i;

        i += 1;
        c = str[i];
    }

    k += 1;

    int L2 = i - k;

    int j;

    char *s2 = (char *)malloc(maxlen * sizeof(char));

    for (j = 0; j < L2; j++)
    {
        if ((j + 1) % 4 == 0)
            s2 = (char *)realloc(s2, (j + maxlen) * sizeof(char));
        s2[j] = str[j + k];
    }

    if (L1 == L2)
    {
        for (j = 0; j < L1; j++)
        {
            str[j] = s2[j];
            str[j + k] = s1[j];
        }
    }
    else if (L1 < L2)
    {
        for (j = k; j > L1; j--)
        {
            str[j + L2 - L1 - 1] = str[j - 1];
        }

        for (j = 0; j < L1; j++)
        {
            str[j + k + L2 - L1] = s1[j];
        }

        for (j = 0; j < L2; j++)
        {
            str[j] = s2[j];
        }
    }
    else if (L1 > L2)
    {
        for (j = L1; j < k; j++)
        {
            printf("%d %d\n", j - (L1 - L2), j);
            printf("%c %c", str[2],str[3]);
            str[2] = str[3];
            printf("AAAAAA\n");
        }

        printf("AAAAAA\n");
        for (j = 0; j < L1; j++)
        {
            str[j + k - (L1 - L2)] = s1[j];
        }

        for (j = 0; j < L2; j++)
        {
            str[j] = s2[j];
        }
    }

    print(str);
    free(s1);
    free(s2);

    return;
}

int main()
{
    char *str = "123+546+12\0";
    printf("%c",str[2]);
    exchange(str);
    putchar(str[2]);

    return 0;
}