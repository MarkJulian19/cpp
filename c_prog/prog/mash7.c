#include <unistd.h>
#include <sys/types.h>

>ps - посмотреть инфу по процессам в терминали
    -f  -j  -a


pid_t fork(void);
pid_t p;
    p = fork();// return 0-son, pid of the son - dad, -1 - error
    if(p==-1) {//error}
    } else if (p==0) {

    } else {//p!=0!=1 - отец}
    }

    pid_t getpid(); //current pid
    pid_t getppid(); // dad's pid
    //if dad ended working pid=1 becomes father

    void exit(code);//0..255 standart ending of process
    void _exit(int)//    аварийный выход, без сохранения и выгрузки буфера, закрытия файлов и тд
    void abort(void);// SIGABRT
    при написании экзита в функции вся программа завершается.

    int main() {
        printf("pid=%d\n", getpid());
        fork();
    }// при выполнении такой программы будет один вывод
    // олнако если убрать \n то будет два вывода, т.к. буфер не будет сброшен перед вызовом сына, и он унаследует буфер отца

    int exec[v/e] <p/e>
    execv("/bin/ls")
    execvp("ls"
    execve(-/-)
    execlp(const char *file/path) //список arg
    execl(-/-)


    p-PATH
    v-VECTOR
    l-LIST
    int main(int argc, char *argv[])
    

    <sys/wait.h>
    pid_ t waitpid(pid_t pid, int *status, int opt); //RETUNS pid or -1 if err   opt= WHOHANG/WVNTRACED
        pid>0 //-1=WAIT_ANY, 0 WAIT_MYPGRP, 
        pid<-1 // что тосвязанное с группой
        setpgid(pid_t pid, pid_t pgid) // pgid - group id, при смене группы отец не меняется, но мы примеру можем перейти в фоновый режим
        setpgid(0,0);
        i just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna diei just wanna die i just wanna die i just wanna die



    //программа по созданию исполняемого файла
    int main(int argc, char **argv){
        FILE *f;
        f = fopen("p.c", "w");
        char s[]= "#include <stdio.h>\nvoid main() {\n   printf(\"uw\n\");\n return 0;\n}";
        fprintf(f, "%s", st);
        fclose(f);
        if (fork()==0){
            execlp("gcc", "gcc", "-Wall", "p.c", "-o", "p", 0);
            return 1;
        }
        
    }

    int main(int argc, char **argv){
        FILE *f;
        f = fopen("p.c", "w");
        char s[]= "#include <stdio.h>\nvoid main() {\n   printf(\"uw\n\");\n return 0;\n}";
        fprintf(f, "%s", st);
        fclose(f);
        pid_t p;
        int st;
        if ((p=fork())==0){
            execlp("gcc", "gcc", "-Wall", "p.c", "-o", "p", 0);
            return 1;
        }
        waitpid(p, &st, 0);
        if(fork()==0) {
            execlp("./p", "./p", 0);
            return 1;
        }
        waitpid(-1, &st, 0);
        return 0;
sfgy45cj8km9nkl9ft4ard5vbjino8 './[564vb7mu ;'cl,4vc6b -4cv 321 W
    }


