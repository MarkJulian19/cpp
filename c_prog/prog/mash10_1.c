#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <stdlib.h>
int p;
void otec(int s)
{
    printf("FATHER\n");
    kill(p, SIGUSR1);
}
void son(int s)
{
    printf("SON\n");
    kill(p, SIGUSR1);
}
void konec(int s)
{
    exit(0);
}

int main()
{
    signal(SIGUSR1, otec);
    p = fork();
    if (p == 0)
    {
        signal(SIGUSR1, son);
        signal(SIGALRM, konec);
        alarm(2);
        p = getppid();
        kill(p, SIGUSR1);
        while (1)
            pause();
    }
    else
    {
        wait(0);
        while (1)
        {
            usleep(1000000);
            printf("FATHER\n");
        }
    }
    return 0;
}
