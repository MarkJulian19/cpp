#include <stdio.h>
#include <stdlib.h>
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
    struct Node *tmp1 = NULL;
    while (tmp){
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
            tmp1->prev=pl->last;
            tmp1->next=NULL;
            pl->last=tmp1;
        }
    }
}
int main(){}