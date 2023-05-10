#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <string.h>

#define f_reverse 1
#define f_space 2
#define f_letters 4
#define f_file 8

int isBigger(char *a, char *b, int parameters) {
	if (parameters & f_space) {
		while (*a == ' ' || *a == '\t')
			a = a+1;
		while (*b == ' ' || *b == '\t')
			b = b+1;
	}
	while (1) {
		if (*a == '\0' && *b == '\0') return 0;
		if (*a == '\0') return (parameters & f_reverse);
		if (*b == '\0') return !(parameters & f_reverse);
		char c1 = *a;
		char c2 = *b;
		if ( parameters & f_letters ) {
			if ( c1 >= 'a' && c1 <= 'z' )
				c1 = c1 ^ 32;
			if ( c2 >= 'a' && c2 <= 'z' )
				c2 = c2 ^ 32;
		}
		if (c1 != c2) {
			if (parameters & f_reverse) {
				return c1 < c2;
			} else {
				return c1 > c2;
			}
		}
		a = a+1;
		b = b+1;
	}
}

int main( int argc, char **argv ) {
	int i,j,k;
	char parameters = 0;
	char *resultFN = NULL;
	FILE *helper;
	char **a;
	for (i = 1; i < argc; i += 1) {
		if ( strcmp(argv[i],"-r") == 0 ) {
			parameters = parameters | f_reverse;
		} else if ( strcmp(argv[i],"-b") == 0 ) {
			parameters = parameters | f_space;
		} else if ( strcmp(argv[i],"-f") == 0 ) {
			parameters = parameters | f_letters;
		} else if ( strcmp(argv[i],"-o") == 0 ) {
			parameters = parameters | f_file;
			i += 1;
			if ( i == argc || resultFN != NULL ) {
				printf("The query is not correct. \n");
			} else {
				resultFN = strdup(argv[i]);
				helper = tmpfile();
			}
		} else {
			FILE *f = fopen(argv[i],"r+");
			if (f == NULL) {
				printf("File is not found. \n");
				break;
			}

			int c, prevC;
			int strCounter = 0;
			while ( (c = fgetc(f)) != EOF ) {
				strCounter += (c == '\n');
				prevC = c;
			}
			if (prevC != '\n') {
				fputc('\n',f);
				strCounter += 1;
			}
			fseek(f,0,SEEK_SET);
			long L = 0;
			int counter;
			a = (char**)malloc(sizeof(char*)*strCounter);
			
			for (int j = 0; j < strCounter; j += 1) {
				counter = 0;
				while ( (c = fgetc(f)) != '\n' ) {
					counter += 1;
				}
				a[j] = (char*)malloc(sizeof(char)*(counter+1));
				fseek(f,L,SEEK_SET);
				for (k = 0; k < counter+1; k += 1) {
					a[j][k] = fgetc(f);
				}
				a[j][counter] = '\0';
				L = ftell(f);
				counter = 0;
			}
			
			for (j = 1; j < strCounter; j += 1) {
				for (k = 1; k < strCounter; k += 1) {
					if ( isBigger(a[k-1],a[k],parameters) ) {
						char *pointer;
						pointer = a[k];
						a[k] = a[k-1];
						a[k-1] = pointer;
					}
				}
			}
			for (j = 0; j < strCounter; j += 1) {
				if ( (parameters & f_file) == 0 ) {
					printf("%s\n",a[j]);
				} else {
					for ( k = 0; a[j][k] != '\0'; k += 1 ) {
						fputc(a[j][k],helper);
					}
					fputc('\n',helper);
				}
			}
			
			if ( (parameters & f_file) == 0 ) {
				printf("<EOF>\n");
			} else {
				fprintf(helper,"<EOF>\n");
			}
			
			for (j = 0; j < strCounter; j += 1)
				free(a[j]);
			fclose(f);
			free(a);
		}
	}
	if (parameters & f_file) {
		fflush(helper);
		fseek(helper,0,SEEK_SET);
		FILE *f = fopen(resultFN,"w");
		int c;
		while ( (c = fgetc(helper)) != EOF ) {
			fputc(c,f);
		}
		free(resultFN);
		fclose(f);
		fclose(helper);
	}
	return 0;
}