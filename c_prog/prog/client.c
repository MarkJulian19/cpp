#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAXSTRLENGTH 100
struct MyMessage
{
    long mtype;
    char str[MAXSTRLENGTH];
};

int main()
{
    int mid, key = 6969, num = 0; //  mid - очередь сообщений; key - ключ очереди сообщений;num - номер клиента
    long mtypee;
    mid = msgget(key, 0666); // открытие очереди сообщений
    struct MyMessage moias;
    while (1)
    {
        // ждём разрешение на очередное считывание
        // первый в первый раз считает 3 и будет отправлять 3, ожидая теперь 4
        // второй считывает 3 и отправляет 4
        msgrcv(mid, &mtypee, sizeof(long), 3 + num % 2, 0);    // получение 3 или 4 как описано выше
        msgrcv(mid, &moias, sizeof(struct MyMessage), num, 0); // получение строки, в первый раз первой в очереди тк num = 0, далее по номеру num
        num = moias.mtype;
        mtypee = 3 + num - 1;
        // вывод строки в конец файла
        if (moias.str[0] != '\0')
        { // если знак конца выходим из цикла
            FILE *F = fopen("text.txt", "a+");
            fprintf(F, "Pid t: %d Str: %s", getpid(), moias.str);
            fclose(F);
        }
        // передача очереди
        msgsnd(mid, &mtypee, sizeof(long), 0);
        if (moias.str[0] == '\0')
            break;
    }
    // отправка информации о завершении
    mtypee = 5;
    msgsnd(mid, &mtypee, sizeof(long), 0);
    return 0;
}