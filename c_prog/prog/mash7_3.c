/*
Работа с файлами и каталогами.
В командной строке передается им я файла.

а) (*) Если этот файл является каталогом выполнить следующие задания:

    - (**) определить, есть ли среди файлов каталога символьные ссылки и вывести для каждой ссылки её собственное имя и номер дескриптора,
    (***) а также имя и номер индексного дескриптора файла, на который она ссылается.

    - создать симфольную ссылку ln -s filename fsymlinkname

    б) (#)Если заданный файл не является каталогом , а обычным файлом:

    - создать файл имя которого образовать из имени исходного файла, приписав к нему суффикс "new".
    (##) Если файл с таким именем уже существует, запросить подтверждение на его изменение.
    Права доступа при создании должны быть заданы так жже как и у исходного.

    - (###) скопировать в файл *new содуржимое исходного файла, поменяв в нем местами первое и последнее слово.

    Слово - последовательноесть символов, ограниченная началом или концом файла или пробельными символами(\n, \t, пробел).

*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>

int main(int argc, char *argv[])
{

    if (argc < 2)
    { // проверка на наличие имени файла
        printf("No file name!\n");
        return 0;
    }
    int fd;
    errno = 0;
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    { // проверка на открытие файла
        printf("Error with file: %d\n", errno);
        return 1;
    }

    struct dirent *rdr=malloc(sizeof(struct dirent));
    struct stat *vstat=malloc(sizeof(struct stat)); // стр-ра стат, в которую будут храниться значения выполн стат макросов
    // struct stat *linkst;

    stat(argv[1], vstat); // выполнение ф-ии стат относительно записанного файла и запись результатов в встат
    if (S_ISDIR(vstat->st_mode))
    { // * выполнение макроса POSIX относительно поля ст_мод, т.к. там хранится флаг, отвечающий за режим доступа
        errno = 0;
        DIR *dir = opendir(argv[1]); //тк мы в теле у.о.=> в аргв был каталог, открываем его
        if (dir == NULL)
        {
            printf("Error with directory: %d\n", errno);
            return 1;
        }

        rdr = readdir(dir); // вызываем функцию риддир относительно указателя каталога, которая сохраняет инф-ю о файле, на который указывает dir в поля структуры dirent rdr
        while (rdr != NULL)
        { //читаем файлы из директории(каталога) до конца
            //printf("fname %s\n", rdr->d_name);

            lstat(rdr->d_name, vstat); // выполняем функцию stat относительно поля имени файла считанного в структуру dirent rdr
            if (S_ISLNK(vstat->st_mode))
            { // вызываем макрос для проверки на симв. строки
                printf("in\n");
                printf("Name of the link: %s, link's descriptor value = %ld\n", rdr->d_name, rdr->d_ino); //(**) условие выполнено, тогда выводим имя ссылки и значение дескриптора, которые уже хранятся в стр-ре rdr
                char *buf = malloc(256);
                readlink(rdr->d_name, buf, 256);
                stat(buf, vstat);
                printf("Name of linked file: %s, file's descriptor = %ld \n", buf, vstat->st_ino);
            }
            rdr = readdir(dir);
        }

        closedir(dir);
        printf(" cool!\n");
    }

    // printf("%d\n", vstat);

    return 0;
}