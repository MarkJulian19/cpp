#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
void recurrent_traversal_dir(char *_work_dir, int n)
{
    DIR *_dirp;
    if ((_dirp = opendir(_work_dir)) == NULL)
    {
        perror("ошибка opendir");
        return;
    }
    struct dirent *_dirent_buf;// = malloc(sizeof(struct dirent));
    struct stat *_stat_buf = malloc(sizeof(struct stat));
    while ((_dirent_buf = readdir(_dirp)) != NULL)
    {
        stat(_dirent_buf->d_name, _stat_buf);
        if ((_dirent_buf->d_type == DT_DIR) && (strcmp(_dirent_buf->d_name, ".") != 0) && (strcmp(_dirent_buf->d_name, "..") != 0))
        {
            int L1 = strlen(_work_dir), L2 = strlen(_dirent_buf->d_name);
            char *_str = malloc(L1 + L2 + 2);
            _str[0] = '\0';
            strcat(_str, _work_dir);
            strcat(_str, "/");
            strcat(_str, _dirent_buf->d_name);
            for (int i = n; i > 0; i--)
                printf("    ");
            printf("Подкаталог: %s\n", _dirent_buf->d_name);
            recurrent_traversal_dir(_str, n + 1);
            free(_str);
        }
        if (((_stat_buf->st_mode & __S_IEXEC) != 0) && (_dirent_buf->d_type != DT_DIR))
        {
            for (int i = n; i > 0; i--)
                printf("    ");
            printf("Исполняемый файл: %s\n", _dirent_buf->d_name);
        }
    }
    closedir(_dirp);
    free(_stat_buf);
}

int main()
{
    char work_dir[255];
    if (getcwd(work_dir, sizeof(work_dir)) == NULL)
    {
        perror("ошибка getcwd");
        return 0;
    }
    else
        printf("Текущий каталог: %s\n\n", work_dir);
    DIR *dirp;
    if ((dirp = opendir(work_dir)) == NULL)
    {
        perror("ошибка opendir");
        return 0;
    }
    struct dirent *dirent_buf;// = malloc(sizeof(struct dirent));
    struct stat *stat_buf = malloc(sizeof(struct stat));
    while ((dirent_buf = readdir(dirp)) != NULL)
    {
        stat(dirent_buf->d_name, stat_buf);
        if ((dirent_buf->d_type == DT_DIR) && (strcmp(dirent_buf->d_name, ".") != 0) && (strcmp(dirent_buf->d_name, "..") != 0))
        {
            printf("Подкаталог текущего каталога: %s Был изменен: %sВссе исполняемые файлы подкаталога: ", dirent_buf->d_name, ctime(&stat_buf->st_ctime));
            int L1 = strlen(work_dir), L2 = strlen(dirent_buf->d_name);
            char *str = malloc(L1 + L2 + 2);
            str[0] = '\0';
            strcat(str, work_dir);
            strcat(str, "/");
            strcat(str, dirent_buf->d_name);
            printf("%s\n", str);
            if ((strcmp(dirent_buf->d_name, ".") != 0) && (strcmp(dirent_buf->d_name, "..") != 0))
            {
                recurrent_traversal_dir(str, 1);
            }
            free(str);
        }
    }
    closedir(dirp);
    free(stat_buf);
    return 0;
}