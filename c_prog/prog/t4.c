#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct Node
{
    struct Node *prev, *next;
    char *elem;
};
struct List
{
    struct Node *first, *last;
};

void process(struct List *pl, const char *str){
    struct Node *tmp = pl->first;
    struct Node *endvalue = pl->last;
    struct Node *tmp1 = NULL;
    while ((tmp != endvalue)&&(tmp != NULL)){
        //printf("%d\n",endvalue);
        //printf("%d\n",tmp);
        if (strcmp(tmp->elem,str)==0){
            tmp1=tmp;
            if (tmp1->prev){
                tmp1->prev->next=tmp1->next;
            }
            if (tmp1->next){
                tmp1->next->prev=tmp1->prev;
            }
            if (!tmp1->prev){
                pl->first=tmp1->next;
            }
            if (!tmp1->next){
                pl->last=tmp1->prev;
            }
            tmp=tmp->next;
            free(tmp1->elem);
            free(tmp1);
            continue;
        }
        if (strcmp(tmp->elem,str)>0){
            tmp1=tmp;
            tmp=tmp->next;
            if (tmp1->prev){
                tmp1->prev->next=tmp1->next;
            }
            if (tmp1->next){
                tmp1->next->prev=tmp1->prev;
            }
            if (!tmp1->prev){
                pl->first=tmp1->next;
            }
            if (!tmp1->next){
                pl->last=tmp1->prev;
            }
            pl->last->next=tmp1;
            tmp1->prev=pl->last;
            tmp1->next=NULL;
            pl->last=tmp1;
        }
        if (tmp != NULL){
            if (strcmp(tmp->elem,str) < 0) tmp=tmp->next;
        }
    }
    //printf("посл эл %s\n",tmp->elem);
    if (tmp != NULL){
        if (strcmp(tmp->elem,str)==0){
            tmp1=tmp;
            if (tmp1->prev){
                tmp1->prev->next=tmp1->next;
            }
            if (tmp1->next){
                tmp1->next->prev=tmp1->prev;
            }
            if (!tmp1->prev){
                pl->first=tmp1->next;
            }
            if (!tmp1->next){
                pl->last=tmp1->prev;
            }
            free(tmp1->elem);
            free(tmp1);
            return;
        }
        if (strcmp(tmp->elem,str)>0){
            if (!tmp->next) return;
            tmp1=tmp;
            if (tmp1->prev){
                tmp1->prev->next=tmp1->next;
            }
            if (tmp1->next){
                tmp1->next->prev=tmp1->prev;
            }
            if (!tmp1->prev){
                pl->first=tmp1->next;
            }
            if (!tmp1->next){
                pl->last=tmp1->prev;
            }
            pl->last->next=tmp1;
            tmp1->prev=pl->last;
            tmp1->next=NULL;
            pl->last=tmp1;
        }       
    }
}


struct List *list_in(struct List *pl)
{
    struct Node *tmp;
    char str[256];
    pl->first = NULL;
    pl->last = NULL;
    while (scanf("%s", str) != EOF)
    {
        if (pl->first == NULL)
        {
            tmp = malloc(sizeof(struct Node));
            pl->first = tmp;
            tmp->prev = NULL;
            tmp->elem = malloc(256);
            strcpy(tmp->elem, str);
            continue;
        }
        else
        {
            tmp->next = malloc(sizeof(struct Node));
            tmp->next->prev = tmp;
            tmp = tmp->next;
            tmp->elem = malloc(256);
            strcpy(tmp->elem, str);
            tmp->next = NULL;
        }
    }
    pl->last = tmp;
    return (pl);
}

void list_out(struct List *pl)
{
    struct Node *tmp = pl->first;
    while (tmp != pl->last)
    {
        printf("%s\n", tmp->elem);
        tmp = tmp->next;
    }
    if (tmp != NULL)
        printf("%s\n", tmp->elem);
}
int main()
{
    struct List *ls = malloc(sizeof(struct List));
    char *str = malloc(256);
    printf("Введите строку:\n");
    scanf("%s", str);
    printf("Введите список:\n");
    ls = list_in(ls);
    printf("Список до изменений:\n");
    list_out(ls);
    printf("Список после изменений:\n");
    process(ls, str);
    list_out(ls);
    return 0;
}