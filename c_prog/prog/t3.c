#include <stdio.h>
int main()
{
    int a, b, n, i, j;
    scanf("%d%d%d", &a, &b, &n);
    for (i = 0; i <= n; i++)
        printf(" ");
    for (i = a; i < b; i++){
        printf("%*d", n, i);
        if (i != (b - 1)) printf(" ");
    }
    printf("\n");
    for (i = a; i < b; i++)
    {
        printf("%*d", n, i);
        printf(" ");
        for (j = a; j < b; j++)
        {
            printf("%*lld", n, (long long)j * i);
            if (j != (b - 1)) printf(" ");
        }
        printf("\n");
    }
    return 0;
}