#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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