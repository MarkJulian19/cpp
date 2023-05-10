#include <stdio.h>
#include <unistd.h>
int main(){
    char c;
    for (int i = 0; i < 2; i ++){
        read(0,&c,1);
        write(1,&c,1);
    }
}