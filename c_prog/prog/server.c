#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAXSTRLENGTH 100
struct msg_send
{
    long mtype;
    char str[MAXSTRLENGTH];
};
int main()
{
    int mid, key = 6969;                 //  mid - очередь сообщений; key - ключ очереди сообщений
    mid = msgget(key, IPC_CREAT | 0666); // создание очереди и её открытие на чтение/запись
    struct msg_send sendit;
    sendit.mtype = 1; // тип первого сообщения
    long start = 3;   // 3 - тип сообщения для первого полученного сообщения первым клиентом и всех вторых клиентов
    FILE *F = fopen("test.txt", "r");
    msgsnd(mid, &start, sizeof(long), 0); // отправка в очередь сообщения о старте, необходимо для определения первого клиента
    while (fgets(sendit.str, MAXSTRLENGTH, F) != NULL)
    {
        puts(sendit.str);
        msgsnd(mid, &sendit, sizeof(struct msg_send), 0); // отправка всех строк из файла в очередь
        sendit.mtype = (sendit.mtype * 2) % 3;            // чередование сообщения типа 1  и  2
    }
    fclose(F);
    // отправка пустых строк для обозначения конца файла
    sendit.str[0] = '\0';
    msgsnd(mid, &sendit, sizeof(struct msg_send), 0);
    sendit.mtype = (sendit.mtype * 2) % 3;
    msgsnd(mid, &sendit, sizeof(struct msg_send), 0);
    // ожидание окончания работы клиентов
    msgrcv(mid, &start, sizeof(long), 5, 0);
    msgrcv(mid, &start, sizeof(long), 5, 0);
    // очистка очередей
    msgctl(mid, IPC_RMID, NULL);
    return 0;
}