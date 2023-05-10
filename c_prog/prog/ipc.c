#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#define NMAX 256
int main(int argc, char **argv)
{
    pid_t pid, pid1;
    if (pid = fork() == 0)
    {
        key_t key, key1;
        int semid, shmid;
        struct sembuf sops;
        char *shmaddr;
        char str[NMAX];
        key = ftok("/usr/", 'L');
        key1 = ftok("/usr/", 'K');
        /* создаем тот же самый ключ */
        semid = semget(key1, 1, 0666 | IPC_CREAT);
        shmid = shmget(key, NMAX, 0666 | IPC_CREAT);
        shmaddr = shmat(shmid, NULL, 0);
        sops.sem_num = 0;
        sops.sem_flg = 0;
        /* запускаем цикл */
        do
        {
            sops.sem_op = -2;
            semop(semid, &sops, 1);
            /* теперь значение семафора равно 1 */
            strcpy(str, shmaddr); /* копируем строку
                из разд.памяти */
            if (str[0] == 'Q')
            {
                /*завершение работы - освобождаем
                разделяемую память */
                shmdt(shmaddr);
            }
            sops.sem_op = 4;
            semop(semid, &sops, 1);
            if (str[0] != 'Q')
            {
                printf("Pid: %d, str: %s\n", getpid(), str);
            }
        } while (str[0] != 'Q');
        return 0;
    }
    if (pid1 = fork() == 0)
    {
        key_t key, key1;
        int semid, shmid;
        struct sembuf sops;
        char *shmaddr;
        char str[NMAX];
        key = ftok("/usr/", 'K');
        /* создаем тот же самый ключ */
        semid = semget(key, 1, 0666 | IPC_CREAT);
        shmid = shmget(key, NMAX, 0666 | IPC_CREAT);
        /* аналогично предыдущему процессу -
        инициализации ресурсов */
        shmaddr = shmat(shmid, NULL, 0);
        sops.sem_num = 0;
        sops.sem_flg = 0;
        /* запускаем цикл */
        do
        {
            sops.sem_op = -4;
            /* будем ожидать, пока не положительно*/
            semop(semid, &sops, 1);
            strcpy(str, shmaddr);
            if (str[0] == 'Q')
            {
                /*завершение работы - освобождаем
                разделяемую память */
                shmdt(shmaddr);
            }
            sops.sem_op = -1;
            semop(semid, &sops, 1);
            if (str[0] != 'Q')
            {
                printf("Pid: %d, str: %s\n", getpid(), str);
            }
        } while (str[0] != 'Q');
        return 0;
    }
    FILE *f = fopen("test.txt", "r+");
    key_t key, key1;
    int semid, shmid, shmid1;
    struct sembuf sops;
    char *shmaddr, *shmaddr1;
    char str[NMAX];
    key = ftok("/usr/", 'K');
    key1 = ftok("/usr/", 'L');
    semid = semget(key, 1, 0666 | IPC_CREAT);
    /* создаем один семафор */
    shmid = shmget(key, NMAX, 0666 | IPC_CREAT);
    /* создаем разделяемую память на 256 элементов*/
    shmaddr = shmat(shmid, NULL, 0);
    shmid1 = shmget(key1, NMAX, 0666 | IPC_CREAT);
    /* создаем разделяемую память на 256 элементов*/
    shmaddr1 = shmat(shmid1, NULL, 0);
    /* подключаемся к разделу памяти*/
    semctl(semid, 0, SETVAL, (int)0);
    /* инициализируем семафор значением 0 */
    sops.sem_num = 0;
    sops.sem_flg = 0;
    int flag = 0;
    do
    { /* запуск цикла */
        if (fgets(str, NMAX, f) == NULL)
        {
            flag = 0;
            strcpy(str, "Q"); /*Признак конца*/
        }
        else
            flag = 1;
        // printf("%s\n", str);
        /* в текущий момент семафор открыт для
        этого процесса */
        strcpy(shmaddr1, str); /* копируем строку в
        разд. память */
        if (fgets(str, NMAX, f) == NULL)
        {
            strcpy(str, "Q"); /*Признак конца*/
        }
        strcpy(shmaddr, str); /* копируем строку в*/
        sops.sem_op = 3;
        semop(semid, &sops, 1);
        sops.sem_op = 0; /* ожидание обнуления
        семафора */
        semop(semid, &sops, 1);
    } while (str[0] != 'Q');
    if (flag == 1)
    {
        strcpy(shmaddr1, "Q");
    }
    /* в данный момент второй процесс уже дочитал
    из разделяемой памяти и отключился от нее –
    можно ее удалять*/
    shmdt(shmaddr); /* отключаемся от разделяемой
    памяти */
    shmdt(shmaddr1);
    shmctl(shmid, IPC_RMID, NULL);
    shmctl(shmid1, IPC_RMID, NULL);
    /* уничтожаем разделяемую память */
    semctl(semid, 0, IPC_RMID, (int)0);
    fclose(f);
    /* уничтожаем семафор */
    return 0;
}