/*
1. Работа с каталогом. Написать программу, которая для текущего каталога выполняет следующие действия:
-если в каталоге есть подкаталоги, вывести на экран их имена и время последнего изменения (см.функцию ctime()),
-рекурсивно обойти все подкаталоги (для всех уровней вложенности) и вывести на экран имена содержащихся в них исполняемых файлов ( т. е. тех, для которых пользователь имеет право на исполнение файла).
 Функцию смены каталога chdir не использовать.

Логинов А.С. 211 гр. ВМК МГУ 2022 
*/


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>
#include <string.h>

void search4dir(DIR *d){
    struct dirent *f_sdir;
    struct stat f_vstat;
    
    f_sdir=readdir(d);
    while (f_sdir != NULL) {
        stat(f_sdir->d_name, &f_vstat);
        if(S_ISDIR(f_vstat.st_mode)) printf("Name of directory: %s,     Time of last modification: %s", f_sdir->d_name, ctime(&f_vstat.st_ctime));
        f_sdir=readdir(d);
    }
    return;
}

void check4x_recursive(char *d){
    struct dirent *f_sdir;
    struct stat f_vstat;
    //int f=0;
    
    f_sdir=readdir(d);
    while(f_sdir!=NULL){
        stat(f_sdir->d_name, &f_vstat);
        if(S_ISDIR(f_vstat.st_mode)) {
            int pre_path=strlen(d), name_of_new_d=strlen(f_sdir->d_name);
            char *path = malloc(pre_path+name_of_new_d+2);
            path[0] = '\0';
            strcat(str, d);
            strcat(str, "/");
            strcat(str, f_sdir->d_name);
            //f_sdir=readdir(d);
            //DIR *dir=opendir(f_sdir->d_name);
            check4x_recursive(dir);
            closedir(dir);
        }
        if(f_vstat.st_mode==S_IXUSR) {
          //if(f+==0) printf()
          printf("Available executable file: %s\n", f_sdir->d_name);
        }
        readdir(d);
    }
    
    return;
}



int main() {
    errno=0;
    DIR *dir = opendir(".");


    if(dir==NULL) {// проверка на открытие каталога
          printf("Error with directory: %d\n", errno);
          return 1;
    }
    int pre_path=strlen(d), name_of_new_d=strlen(f_sdir->d_name);
    char *path = malloc(pre_path+name_of_new_d+2);
    path[0] = '\0';
    strcat(path, d);
    strcat(path, "/");
    strcat(path, sdir->d_name);
    search4dir(dir);
    check4x_recursive(dir);
    closedir(dir);    
    printf("Debug\n");
    return 0;
}

