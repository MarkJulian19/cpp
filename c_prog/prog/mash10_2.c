#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/file.h>
int p;
int fd;
void otec(int s)
{
    char c;
    int x;
    while ((x = read(fd, &c, 1)) == 1 && c != ' ' && c != '\n')
        putchar(c);
    if (x != 0)
    {
        printf(" FATHER\n");
        kill(p, SIGUSR1);
    }
}
void son(int s)
{
    char c;
    int x;
    while ((x = read(fd, &c, 1)) == 1 && c != ' ' && c != '\n')
        putchar(c);

    if (x != 0)
    {
        printf(" SON\n");
        kill(p, SIGUSR1);
    }
}
void konec(int s)
{
    exit(0);
}

int main(int argc, char *argv[])
{
    fd = open(argv[1], O_RDONLY);
    signal(SIGUSR1, otec);
    p = fork();
    if (p == 0)
    {
        signal(SIGUSR1, son);
        signal(SIGALRM, konec);
        alarm(1);
        p = getppid();
        kill(p, SIGUSR1);
        while (1)
            pause();
    }
    wait(0);
    close(fd);
    return 0;
}
