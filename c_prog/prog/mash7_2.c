#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
int main(int argc, char **argv)
{   
    struct dirent *ins = malloc(sizeof(struct dirent));
    struct stat *buf = malloc(sizeof(struct stat));
    struct stat *finf = malloc(sizeof(struct stat));
    stat(argv[1], buf);
    if (!S_ISDIR(buf->st_mode))
        return 0;
    DIR *dp;
    char *linkbuf = malloc(256);
    dp = opendir(argv[1]);
    while ((ins = readdir(dp)) != NULL)
    {
        lstat(ins->d_name, finf);
        if (S_ISLNK(finf->st_mode))
        {
            printf("%ld %s\n", ins->d_ino, ins->d_name);
            readlink(ins->d_name, linkbuf, 256);
            stat(linkbuf, finf);
            printf("%ld %s\n", finf->st_ino, linkbuf);
        }
    }
    closedir(dp);
    free(buf);
    free(finf);
    free(ins);
    return 0;
}