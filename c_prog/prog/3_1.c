#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _sym{
    char simb;
    struct _sym *sledbukva;
}sym;

typedef struct _Node
{
    sym *bukva;
    char *str;
    int size;
    struct _Node *prev;
    struct _Node *next;
}Node;

typedef struct _DBLIST{
    Node *head;
    Node *tail;

}DBLIST;

void deleteDBLIST(DBLIST **list) {
    Node *tmp = (*list)->head;
    sym *tmp1;
    Node *next = NULL;
    sym *next1 = NULL;
    while (tmp) {
        tmp1 = tmp->bukva;
        while (tmp1){
            next1 = tmp1->sledbukva;
            free(tmp1);
            tmp1 = next1;
        }
        free(tmp->str);
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}
/*
void pushFront(DBLIST *list) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(1);
    }
    tmp->bukva = NULL;
    tmp->next = list->head;
    tmp->prev = NULL;
    if (list->head) {
        list->head->prev = tmp;
    }
    list->head = tmp;
 
    if (list->tail == NULL) {
        list->tail = tmp;
    }
    list->size++;
}*/

void pushBackDBLIST(DBLIST *list) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(3);
    }
    tmp->size=0;
    tmp->bukva = NULL;
    tmp->next = NULL;
    tmp->prev = list->tail;
    if (list->tail) {
        list->tail->next = tmp;
    }
    list->tail = tmp;
 
    if (list->head == NULL) {
        list->head = tmp;
    }
}

void printDBLISTR(DBLIST *list){
    Node *tmp = list->head;
    sym *tmp1;
    char *str1;
    while (tmp){
        tmp1=tmp->bukva;
        while (tmp1){
            printf("%c",tmp1->simb);
            tmp1=tmp1->sledbukva;
        }
        printf(" %d",tmp->size);
        tmp = tmp->next;
        printf("\n");
    }
}

void printDBLISTL(DBLIST *list){
    Node *tmp = list->tail;
    sym *tmp1;
    while (tmp){
        tmp1=tmp->bukva;
        while (tmp1){
            printf("%c",tmp1->simb);
            tmp1=tmp1->sledbukva;
        }
        tmp = tmp->prev;
        printf("\n");
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

void pushBacklist(sym *head, char value) {
    sym *last = getLast(head);
    sym *tmp = (sym*) malloc(sizeof(sym));
    tmp->simb = value;
    tmp->sledbukva = NULL;
    last->sledbukva = tmp;
}


DBLIST* createDBLIST() {
    DBLIST *tmp = (DBLIST*) malloc(sizeof(DBLIST));
    tmp->head = tmp->tail = NULL;
    printf("Двунаправленный список был создан, введите строку:\n");
    char c;
    int i=0;
    while(((c = getchar()) != '\n')&&(c!= EOF)){
        if (c!=' '){
            pushBackDBLIST(tmp);
            sym *p= (sym*) malloc(sizeof(sym));
            pushBacklist (p,c);
            i++;
            while(((c = getchar())!= ' ')&&(c != '\n')&&(c != EOF)){
                pushBacklist(p,c);
                i++;
            }
            tmp->tail->bukva=p;
            tmp->tail->size=i;
            i=0;
            if ((c == '\n')||(c == EOF)) break;
        }
    }    
    return tmp;
}    

int main(){
    DBLIST *list = createDBLIST();
    printDBLISTR(list);
    printDBLISTL(list);
    deleteDBLIST(&list);
    return 0;
}