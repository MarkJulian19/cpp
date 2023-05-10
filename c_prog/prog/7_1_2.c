#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/file.h>
#include <time.h>

/*Фомин Дмитрий 211*/

/* в аргументах при запуске надо задать полный путь
 * до той директории, которая интересна */

void recursDialoges( char **path, char *endstr, int *len, int level ) {
	DIR *dp = opendir(*path);
	if (dp == NULL)
		return;
	struct dirent *cmp;
	struct stat buf;
	while ( (cmp = readdir(dp)) != NULL ) {
		if ( strcmp(cmp->d_name,".") == 0 || strcmp(cmp->d_name,"..") == 0 ) {
			continue;
		}
		*endstr = '/';
		strcpy(endstr+1, cmp->d_name);
		if ( !stat(*path,&buf) ) {
			if (S_ISDIR(buf.st_mode)) {
				for (int i = 0; i < level*2; i += 1)
					putchar(' ');
				printf("%s %s",cmp->d_name, ctime( &buf.st_mtime ));
				/* putchar(' ') - это для красивого вывода */
				for (int i = 0; i < level*2; i += 1)
					putchar(' ');
				putchar('{');
				putchar('\n');
				int k = strlen(cmp->d_name) + 1;
				int h = endstr-*path;
				/* каждый раз в буфере должно быть достатточно места для
				 * имени нового файла, так что используем realloc */
				if ( h + k + 257 > *len ) {
					*len = h + k + 257;
					*path = realloc(*path, *len);
					endstr = (*path) + h;
				}
				recursDialoges(path,endstr+k,len,level+1);
				endstr = *path + h;
				/* последняя строка нужна, тк в более нижнем слое
				 * рекурсии мог быть вызван realloc */
				for (int i = 0; i < level*2; i += 1)
					putchar(' ');
				putchar('}');
				putchar('\n');
			} else {
				int i = buf.st_mode;
				if (i & 0b1000000) {
					for (int i = 0; i < level*2; i += 1)
						putchar(' ');
					printf("%s\n",cmp->d_name );
				}
			}
		}
	}
	closedir(dp);
	return;
}

int main( int argc, char **argv ) {
	if (argc == 0) {
		printf("write path!");
		return 0;
	}
	int len = strlen(argv[1])+257;
	char *c = (char*)malloc(len);
	strcpy(c,argv[1]);
	/* строка c пройдёт по ссылке по любой глубине рекурсии,
	 * endstr будет создаваться каждый раз заново и указывать на конец
	 * пути до текущего файла, именно к endstr будет добавляться новое
	 * имя файла */
	char *endstr = c + strlen(argv[1]);
	recursDialoges(&c,endstr,&len,0);
	free(c);
	return 0;
}