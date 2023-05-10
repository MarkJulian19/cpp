#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    pid_t pros1, pros2;
    int pipefd[2];
    pipe(pipefd);
    if ((pros1 = fork()) == -1)
        return -1;
    if (pros1 == 0)
    {
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        close(pipefd[1]);
        execl(argv[1], argv[1], NULL);
    }
    if ((pros2 = fork()) == -1)
        return -1;
    else if (!pros2)
    {
        close(pipefd[1]);
        dup2(pipefd[0], 0);
        close(pipefd[0]);
        execl(argv[2], argv[2], NULL);
        exit(2);
    }
    close(pipefd[1]);
    waitpid(pros2, NULL, 0);
    char buf[512];
    ssize_t len;
    while ((len = read(pipefd[0], buf, 512)) > 0)
        write(1, buf, len);
    close(pipefd[0]);
    wait(NULL);
    return 0;
}