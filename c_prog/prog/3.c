#include <stdio.h>
int main(int argc, char char *argv[]);
ls -l -a
gcc f.c
extern char **environ
char *getenv (const char *str)
int putenv (const char *str1)
int atoi(str)
atof
double strtod(const char *str, char **end)
long strtol(onst char *str, char end, int basis)
sscanf(str,формат,адреса)
sprintf(str,формат,адреса)
./a.aut 3 ab abc abcde 
int main(int argc,char *argr[]){
    int strsize, size;
    char *p;
    if (argc < 3)
        return 0;
    size = strtol(argv[1],NULL,10);
    for (int i = 2, i<argc,i++){
        p = argv[i];
        strsize = strlen(argv[i]);
        if (strsize <= size){
            printf("%s=%s\n", p, p);
            continue;  

        }
    printf("%.*s=",size,p);
    printf("%s", (p+strsize)-size);
    }
    return 0;
}
struct s{int i;
        double d1,d2;
        };
struct S
{
    struct S *p;
    struct S1 S1;
}
typedef struct list{int i;
                struct list *next;}
                }
