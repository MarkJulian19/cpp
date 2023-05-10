#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <termios.h>
#include <limits.h>
#define menu_slots 4
#define maska (128+8)
#define clearflag 1
//(10001000)
static struct termios stored;

const int maximlen = 128;

void init() {
    struct termios settings;
 
    tcgetattr(0, &stored);
 
    settings = stored;
 
    settings.c_lflag &= (~ICANON);
    settings.c_lflag &= (~ECHO);
    settings.c_cc[VTIME] = 0;
    settings.c_cc[VMIN] = 1;
 
    tcsetattr(0, TCSANOW, &settings);
}
 
void reset() {
    struct termios settings;
 
    tcgetattr(0, &stored);
 
    settings = stored;
 
    settings.c_lflag |= (ICANON);
    settings.c_lflag |= (ECHO);
 
    tcsetattr(0, TCSANOW, &settings);

}

void f1(){
    printf("bruh\n");
}

void say(){
    system("clear");
    printf("Введите имя файла:\n");
    char buf[PATH_MAX];
    scanf("%s", buf);
    FILE *F;
    F = fopen(buf,"r");
    char c;
    while (fscanf(F,"%c",&c) != -1){
        printf("%c",c);
    }
    
}
void shifr(){
      system("clear");
    printf("Введите имя файла:\n");
    char buf[PATH_MAX];
    scanf("%s", buf);
    FILE *F, *Fnew;
    F = fopen(buf,"r");
    Fnew = tmpfile();
    char c;

    while (fscanf(F,"%c",&c) != -1){
        c = (c & (~maska))|((~c) & maska);
        fputc(c,Fnew);
    }
    fseek(Fnew, 0, SEEK_SET);
    fclose(F);
    F = fopen(buf,"w");
    while (fscanf(Fnew,"%c",&c) != -1)
        fputc(c,F);
    fclose(F);
    fclose(Fnew);
}

    

void print_menu(char ** m, int n){
    for (int i = 0; i < menu_slots;i++){
        if (i == n) printf(">");
        else printf(" ");
        printf("%s\n", m[i]);
    }
    
}

void starter(char* name){
    if (strcmp(name,"f1") == 0) f1();
    if (strcmp(name,"shifr") == 0) shifr();
    if (strcmp(name,"deshifr") == 0) shifr();
    if (strcmp(name,"say") == 0) say();
}

void menu(char ** m, char ** fun,int flag){
    char ch;
    int n = 0;
    init();
    if (flag)
        system("clear");
    print_menu(m,n);
    while (1) {
        ch = getc(stdin);
        if (ch == 27){
            ch = getc(stdin);
            if (ch == 91){
                ch = getc(stdin);
                // 65-up 66-down
                if (ch == 65 && n > 0) 
                    n--;
                if (ch == 66 && n < menu_slots-1)
                    n++;   
            }
        }
        if (ch == '\n'){
            reset();
            if (n == menu_slots-1) return;
            starter(fun[n]);
            init();
            printf("\n");
            print_menu(m,n);
            getc(stdin);
            
        }
        else {
            if (flag)
                system("clear");
            else printf("\n\n\n");
            print_menu(m,n);
            
        }
    }
}



int main(){
    char * m[menu_slots], * fun[menu_slots];
    m[0] = malloc(25*sizeof(char));
    m[1] = malloc(15*sizeof(char));
    m[2] = malloc(17*sizeof(char));
    m[3] = malloc(6*sizeof(char));
    stpcpy(m[0],"Вывести файл на экран");
    stpcpy(m[1],"Шифровать файл");
    stpcpy(m[2],"Дешифровать файл");
    stpcpy(m[3],"Выход");
    fun[0] = malloc(2*sizeof(char));
    fun[1] = malloc(2*sizeof(char));
    fun[2] = malloc(2*sizeof(char));
    fun[3] = malloc(2*sizeof(char));
    strcpy(fun[0], "say");
    strcpy(fun[1], "shifr");
    strcpy(fun[2], "deshifr");

    menu(m,fun,clearflag);
    printf("Программа закончила своё выполнение\n");
    return 0;
}
