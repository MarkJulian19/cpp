#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
    pid_t B;
    if(B=fork()>0){
        usleep(2000000);
        printf("родительский процесс\n");
    }
    else{
        usleep(1000000);
        printf("ребенок\n");
    }

    printf("%d\n", getpid());
    return 0;
}