#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _sym{
    char simb;
    struct _sym *sledbukva;
}sym;

typedef struct _Node
{
    char *str;
    struct _Node *prev;
    struct _Node *next;
}Node;

typedef struct _DBLIST{
    Node *head;
    Node *tail;

}DBLIST;

void deleteDBLIST(DBLIST **list) {
    Node *tmp = (*list)->head;
    Node *next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp->str);
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}

void deleteLIST(sym **p) {
    sym *q;
    while(*p != NULL) {
        q = *p;
        *p = (*p)->sledbukva;
        free(q);
    }
}

char* createSTR(sym *p, int size) {
    char *s = malloc(size + 1);
    int i = 0;
    while(p != NULL) {
        s[i++] = p->simb;
        p = p->sledbukva;
    }
    s[i] = 0;
    return s;
}

void pushBackDBLIST(DBLIST **list, sym *p, int size) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->str = createSTR(p, size);
    tmp->next = NULL;
    tmp->prev = (*list)->tail;
    if ((*list)->tail) 
        (*list)->tail->next = tmp;
    (*list)->tail = tmp;
    if ((*list)->head == NULL)
        (*list)->head = tmp;
}

void pushSortDBLIST(DBLIST **list, sym *p, int size)
{
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->str = createSTR(p, size);
    Node *l = (*list)->head, *q = (*list)->head;
    while(l != NULL && strcmp(tmp->str, l->str) >= 0) {
        q = l;
        l = l->next;
    }
    if(l == q) {
        tmp->next = (*list)->head;
        tmp->prev = NULL;
        (*list)->head = tmp;
    }
    else {
        tmp->next = l;
        tmp->prev = q;
        if(l != NULL)
            l->prev = tmp;
        q->next = tmp;
    }
    if(tmp->next == NULL)
        (*list)->tail = tmp;
}

void printDBLISTR(DBLIST *list){
    Node *tmp = list->head;
    while (tmp) {
        puts(tmp->str);
        tmp = tmp->next;
    }
}

void printDBLISTL(DBLIST *list) {
    Node *tmp = list->tail;
    while (tmp) {
        puts(tmp->str);
        tmp = tmp->prev;
    }
}

sym* getLast(sym *head) {
    if (head == NULL) {
        return NULL;
    }
    while ((head->sledbukva) != NULL) {
        head = head->sledbukva;
    }
    return head;
}

void pushBacklist(sym **head, char value) {
    sym *last = getLast(*head);
    sym *tmp = (sym*) malloc(sizeof(sym));
    tmp->simb = value;
    tmp->sledbukva = NULL;
    if(last != NULL)
        last->sledbukva = tmp;
    else
        *head = tmp;
}

void createDBLIST(DBLIST **list, DBLIST **list1) {
    DBLIST *tmp = (DBLIST*) malloc(sizeof(DBLIST)), *tmp1 = (DBLIST*) malloc(sizeof(DBLIST));
    sym *p = NULL;
    tmp->head = tmp->tail = NULL;
    tmp1->head = tmp1->tail = NULL;
    printf("Двунаправленный список был создан, введите строку:\n");
    char c;
    int i = 0;
    while(((c = getchar()) != '\n')&&(c!= EOF)){
        if (c!=' '){
            pushBacklist (&p,c);
            i++;
            while(((c = getchar())!= ' ')&&(c != '\n')&&(c != EOF)){
                pushBacklist(&p,c);
                i++;
            }
            pushBackDBLIST(&tmp, p, i);
            pushSortDBLIST(&tmp1, p, i);
            deleteLIST(&p);
            i=0;
            if ((c == '\n')||(c == EOF)) break;
        }
    }
    *list = tmp;
    *list1 = tmp1;
}

int main(){
    DBLIST *list, *list1;
    createDBLIST(&list, &list1);
    printDBLISTR(list);
    printf("\n");
    printDBLISTL(list);
    printf("\n");
    printDBLISTR(list1);
    deleteDBLIST(&list);
    deleteDBLIST(&list1);
    return 0;
}