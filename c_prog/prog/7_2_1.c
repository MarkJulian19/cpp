#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
void print_menu()
{
    system("clear");
    printf("1-Вывести файл на экран\n");
    printf("2-Зашифровать файл\n");
    printf("3-Дешифровать файл\n");
    printf("4-Выход\n");
    printf(">");
    return;
}
void print_f()
{
    system("clear");
    printf("Введите имя файла:\n");
    char buf[PATH_MAX];
    scanf("%s", buf);
    FILE *F;
    F = fopen(buf, "r");
    if (F == NULL)
    {
        printf("Неверный параметр, попробуйте еще раз через:\n");
        for (int i = 5; i > 0; i--)
        {
            printf("%dсек...\n", i);
            usleep(1000000);
        }
        return;
    }
    char c;
    while (fscanf(F, "%c", &c) != -1)
    {
        printf("%c", c);
    }
    printf("\n");
    for (int i = 15; i > 0; i--)
    {
        printf("%dсек...\n", i);
        usleep(1000000);
    }
}
void shifr_f()
{
    system("clear");
    printf("Введите имя файла:\n");
    char buf[PATH_MAX];
    scanf("%s", buf);
    FILE *F, *tmpf;
    F = fopen(buf, "r");
    if (F == NULL)
    {
        printf("Неверный параметр, попробуйте еще раз через:\n");
        for (int i = 5; i > 0; i--)
        {
            printf("%dсек...\n", i);
            usleep(1000000);
        }
        return;
    }
    tmpf = tmpfile();
    char c;
    long long n = -1123;
    while (fscanf(F, "%c", &c) != -1)
    {
        c = c + n + 8;
        n++;
        fputc(c, tmpf);
    }
    fseek(tmpf, 0, SEEK_SET);
    fclose(F);
    F = fopen(buf, "w");
    while (fscanf(tmpf, "%c", &c) != -1)
        fputc(c, F);
    fclose(F);
    fclose(tmpf);
}
void deshifr_f()
{
    system("clear");
    printf("Введите имя файла:\n");
    char buf[PATH_MAX];
    scanf("%s", buf);
    FILE *F, *tmpf;
    F = fopen(buf, "r");
    if (F == NULL)
    {
        printf("Неверный параметр, попробуйте еще раз через:\n");
        for (int i = 5; i > 0; i--)
        {
            printf("%dсек...\n", i);
            usleep(1000000);
        }
        return;
    }
    tmpf = tmpfile();
    char c;
    long long n = -1123;
    while (fscanf(F, "%c", &c) != -1)
    {
        c = c - n - 8;
        n++;
        fputc(c, tmpf);
    }
    fseek(tmpf, 0, SEEK_SET);
    fclose(F);
    F = fopen(buf, "w");
    while (fscanf(tmpf, "%c", &c) != -1)
        fputc(c, F);
    fclose(F);
    fclose(tmpf);
}

int main()
{
    while (1)
    {
        print_menu();
        int x;
        scanf("%d", &x);
        if (x == 1)
        {
            print_f();
            continue;
            ;
        }
        if (x == 2)
        {
            shifr_f();
            continue;
        }
        if (x == 3)
        {
            deshifr_f();
            continue;
        }
        if (x == 4)
        {
            system("clear");
            return 0;
        }
        printf("Неверный параметр, попробуйте еще раз через:\n");
        for (int i = 5; i > 0; i--)
        {
            printf("%dсек...\n", i);
            usleep(1000000);
        }
    }

    return 0;
}