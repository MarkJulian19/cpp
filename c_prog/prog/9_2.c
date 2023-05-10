#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/file.h>
#include <stdlib.h>
#include <sys/wait.h>
// 0 - чтение
// 1 - запись
int main(int argc, char **argv)
{
    if (argc < 2) return 0;
    int f;
    if ((f = open(argv[1], O_RDWR | O_CREAT, 0777)) == -1) return 0;
    int fd1[2];
    pipe(fd1);
    char c;
    char space = ' ';
    char s[81];
    printf("char string\n");
    int p = fork();
    if (p == 0)
    {
        close(fd1[1]);
        while (read(fd1[0], &c, 1))
        {
            int count = 0;
            char temp;
            while (read(fd1[0], &temp, 1) && temp != ' ')
            {
                if (temp == c)
                    count++;
            }
            sprintf(s, "%d\n", count);
            printf("%s", s);
            write(f, &space, 1);
            write(f, s, strlen(s));
        }
        close(fd1[0]);
        exit(0);
    }
    else
    {
        close(fd1[0]);
        while (read(0, &c, 1) && c != '\0' && c != '\n')
        {
            char temp;
            if (!read(0, &temp, 1)) break;
            int i = 0;
            while (read(0, &temp, 1) && temp != '\n' && temp != '\0')
            {
                s[i] = temp;
                i++;
            }
            s[i] = '\0';
            if (strcmp(s, "exit") == 0) break;
            else
            {
                write(f, &c, 1);
                write(f, &space, 1);
                write(f, s, i);
                write(fd1[1], &c, 1);
                write(fd1[1], s, i);
                write(fd1[1], &space, 1);
            }
            strcpy(s,"");
        }
        close(fd1[1]);
        close(f);
        wait(0);
    }
    return 0;
}