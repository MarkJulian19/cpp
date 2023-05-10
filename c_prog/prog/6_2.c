#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <string.h>

void str_count(FILE *f, int *a)
{
    while ((a[2] = fgetc(f)) != EOF)
    {
        a[0] += (a[2] == '\n');
        a[1] = a[2];
    }
    return;
}

int bigger(char *a, char *b, int param)
{
    if (param & 2)
    {
        while ((*a == ' ') || (*a == '\t')) a++;
        while ((*b == ' ') || (*b == '\t')) b++;
    }
    while (1)
    {
        if ((*a == '\0') && (*b == '\0')) return 0;
        if (*a == '\0') return (param & 1);
        if (*b == '\0') return !(param & 1);
        char a_ = *a;
        char b_ = *b;
        if (param & 4)
        {
            if ((a_ >= 'a') && (a_ <= 'z')) a_ = a_ ^ 32;
            if ((b_ >= 'a') && (b_ <= 'z')) b_ = b_ ^ 32;
        }
        if (a_ != b_)
        {
            if (param & 1) return a_ < b_;
            else return a_ > b_;
        }
        a++;
        b++;
    }
}

void sort(int count, char **arr, char param)
{
    int i, j, k;
    for (j = 1; j < count; j++)
    {
        for (k = 1; k < count; k++)
        {
            if (bigger(arr[k - 1], arr[k], param))
            {
                char *point;
                point = arr[k];
                arr[k] = arr[k - 1];
                arr[k - 1] = point;
            }
        }
    }
    return;
}

int main(int argc, char **argv)
{
    char param = 0;
    char *res_FN = NULL;
    FILE *tmp_f; 
    int i, j, k;
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-r") == 0) param = param | 1;
        else if (strcmp(argv[i], "-b") == 0) param = param | 2;
        else if (strcmp(argv[i], "-f") == 0) param = param | 4;
        else if (strcmp(argv[i], "-o") == 0)
        {
            param = param | 8;
            i++;
            if ((i == argc) || (res_FN != NULL)) printf("not_corr\n");
            else
            {
                res_FN = strdup(argv[i]);
                tmp_f = tmpfile();
            }
        }
        else
        {
            FILE *f = fopen(argv[i], "r+");
            if (f == NULL)
            {
                printf("erf\n");
                break;
            }
            int c;
            int *a = malloc(sizeof(int) * 3);
            str_count(f, a);
            if (a[1] != '\n')
            {
                fputc('\n', f);
                a[0] += 1;
            }
            fseek(f, 0, SEEK_SET);
            int ctr;
            char **b;
            b = (char **)malloc(sizeof(char *) * a[0]);
            int p1 = 0;
            for (int j = 0; j < a[0]; j++)
            {
                ctr = 0;
                while ((c = fgetc(f)) != '\n')
                {
                    ctr += 1;
                }
                b[j] = (char *)malloc(sizeof(char) * (ctr + 1));
                fseek(f, p1, SEEK_SET);
                for (k = 0; k < ctr + 1; k++)
                {
                    b[j][k] = fgetc(f);
                }
                b[j][ctr] = '\0';
                p1 = ftell(f);
                ctr = 0;
            }
            sort(a[0], b, param);
            for (j = 0; j < a[0]; j++)
            {
                if ((param & 8) == 0) printf("%s\n", b[j]);
                else
                {
                    for (k = 0; b[j][k] != '\0'; k++)
                    {
                        fputc(b[j][k], tmp_f);
                    }
                    fputc('\n', tmp_f);
                }
            }
            for (j = 0; j < a[0]; j++)
                free(b[j]);
            free(a);
            fclose(f);
            free(b);
        }
    }
    if (param & 8)
    {
        fflush(tmp_f);
        fseek(tmp_f, 0, SEEK_SET);
        FILE *f = fopen(res_FN, "w");
        int c;
        while ((c = fgetc(tmp_f)) != EOF)
        {
            fputc(c, f);
        }
        free(res_FN);
        fclose(f);
        fclose(tmp_f);
    }
    return 0;
}