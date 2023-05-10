#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
int main(int argc, char **argv)
{
    if (argc < 2)
        return 0;
    int f = open(argv[1], O_RDONLY | O_APPEND, 0777);
    int size = lseek(f, 0, SEEK_END);
    char tmp[size * 2];
    int counter = atoi(argv[2]);
    lseek(f, 0, SEEK_SET);
    if (size >= 1024)
    {
        close(f);
        return 0;
    }
    int cntrl;
    int tmp_f = open("tmp", O_CREAT | O_RDWR, 0777);
    while ((cntrl = read(f, tmp, counter)) != 0)
    {
        write(tmp_f, tmp, cntrl);
        write(tmp_f, tmp, cntrl);
    }
    lseek(tmp_f, 0, SEEK_SET);
    close(f);
    f = open(argv[1], O_TRUNC | O_WRONLY, 0777);
    read(tmp_f, tmp, size * 2);
    write(f, tmp, size * 2);
    remove("tmp");
    close(f);
    return 0;
}