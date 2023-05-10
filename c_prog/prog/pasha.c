#include <stdio.h>
#include <stdlib.h>
typedef struct _predloz
{
    char *slovo;
    struct _predloz *next_slovo;
} predloz;

typedef struct _text
{
    predloz *predl;
    struct _text *next_predl;
} text;

typedef struct _ochered
{
    text *first;
    text *last;
    int size;
} ochered;

/*predloz *create_predloz()
{
    predloz *first = NULL;
    predloz *predl = NULL;
    predloz *tmp_predl = NULL;
    char c;
    while (1)
    {
        printf("Введите + для добавления слова в предложение либо / для конца ввода слов в предложение\n");
        scanf("%c", &c);
        if (c == '/')
            break;
        else if (c == '+')
        {
            if (first == NULL)
            {
                int j = 0;
                first = (predloz *)malloc(sizeof(predloz));
                char *tmp_str = (char *)malloc(sizeof(char) * 100);
                c = getchar();
                while ((c = getchar()) && c != EOF && c != '\n')
                {
                    tmp_str[j] = c;
                    j++;
                }
                tmp_str[j] = '\0';
                first->slovo = tmp_str;
                first->next_slovo = NULL;
                predl = first;
            }
            else
            {
                int j = 0;
                tmp_predl = (predloz *)malloc(sizeof(predloz));
                char *tmp_str = (char *)malloc(sizeof(char) * 100);
                c = getchar();
                while ((c = getchar()) && c != EOF && c != '\n')
                {
                    tmp_str[j] = c;
                    j++;
                }
                tmp_str[j] = '\0';
                tmp_predl->slovo = tmp_str;
                tmp_predl->next_slovo = NULL;
                predl->next_slovo = tmp_predl;
                predl = tmp_predl;
            }
        }
    }
    return first;
}
*/

void print_spisok(predloz *head, predloz *ptr)
{
    int i;
    // system("clear");
    while (head != NULL)
    {
        if (head == ptr)
        {
            for (i = 0; head->slovo[i] != '\n'; i++)
                printf("\x1b[31m%c\x1b[0m", head->slovo[i]);
            printf(" ");
        }
        else
        {
            for (i = 0; head->slovo[i] != '\n'; i++)
                printf("%c", head->slovo[i]);
            printf(" ");
        }
        head = head->next_slovo;
    }
    printf("\n");
    return;
}

predloz *clear_1(predloz *head)
{
    predloz *tmp_predl = head;
    while (tmp_predl != NULL)
    {
        head = head->next_slovo;
        free(tmp_predl);
        tmp_predl = head;
    }
    printf("list is empty\n");
    return head;
}

int check_end(predloz *ptr)
{
    predloz *tmp = ptr;
    if (tmp->next_slovo == NULL)
    {
        printf("Ukaz in the end\n");
    }
    else
        printf("Ukaz not in the end\n");

    return 0;
}

int check_pust(predloz *head)
{
    system("clear");
    if (head == NULL)
    {
        printf("Spisok pust\n");
        return 0;
    }
    else
    {
        printf("Spisok ne pust\n");
        return 1;
    }
}

predloz *get_elem(predloz *head, predloz *ptr)
{
    predloz *temp = ptr;

    if (temp->next_slovo != NULL)
    {
        temp = temp->next_slovo;
        return temp;
    }
    else
    {
        print_spisok(head, ptr);
        printf("Net sled elem\n");
        return NULL;
    }
}

predloz *set_start(predloz *head)
{
    printf("Yes!\n");
    return head;
}

predloz *pokaz_elem(predloz *head, predloz *ptr)
{
    predloz *tmp_predl = ptr->next_slovo;
    if (!tmp_predl)
    {
        return NULL;
    }
    else
    {
        ptr->next_slovo = ptr->next_slovo->next_slovo;
        return tmp_predl;
    }
}

predloz *go_next(predloz *head, predloz *ptr)
{
    predloz *tmp = ptr;

    if (tmp->next_slovo != NULL)
    {
        tmp = tmp->next_slovo;
        ptr = tmp;
        print_spisok(head, ptr);
    }
    else
    {
        print_spisok(head, ptr);
        printf("Ukaz in the end\n");
    }

    return ptr;
}
void vyvod_elementa(predloz *elem)
{
    int i;
    predloz *tmp = elem;
    for (i = 0; tmp->slovo[i] != '\n'; i++)
    {
        printf("%c", tmp->slovo[i]);
    }
    printf("\n");
    return;
}

void remove_elem(predloz *head, predloz *ptr)
{
    predloz *tmp_predl;
    if (ptr->next_slovo != NULL)
    {
        tmp_predl = ptr->next_slovo;
        ptr->next_slovo = ptr->next_slovo->next_slovo;
        free(tmp_predl);
    }
    else
        printf("Next elem is empty");
    print_spisok(head, ptr);
    return;
}

predloz *create_node()
{
    char c = ' ';
    int i = 0;
    predloz *node = (predloz *)malloc(sizeof(predloz));
    if (node == NULL)
    {
        printf("Not memorry\n");
        // exit(1);
    }
    node->slovo = (char *)malloc(sizeof(char *));
    if (node->slovo == NULL)
    {
        printf("Not memorry\n");
        free(node);
        // exit(1);
    }

    printf("Vvedite slovo\n");
    c = getchar();
    c = ' ';
    for (i; c != '\n'; i++)
    {
        node->slovo = realloc(node->slovo, (i + 1) * sizeof(char));
        if (!node->slovo)
        {
            printf("Not memorry!\n");
            free(node);
            // exit(1);
        }
        c = getchar();
        node->slovo[i] = c;
    }
    node->slovo[i] = 0;

    node->next_slovo = NULL;
    return node;
}

void change_elem(predloz *head, predloz *ptr)
{
    predloz *temp = ptr;
    predloz *pointer = ptr;

    if (temp->next_slovo != NULL)
    {
        temp = temp->next_slovo;
    }
    else
    {
        printf("there is no word behind the pointer\n");
        return;
    }

    predloz *new_elem = create_node();

    pointer->next_slovo = new_elem;
    new_elem->next_slovo = temp->next_slovo;

    free(temp);

    print_spisok(head, ptr);
    return;
}

/*void add_elem(predloz* head, predloz* ty, predloz* ptr) {
    predloz* new_el = ty;
    predloz* tmp = head;
    if (tmp->next != NULL)
    {
        while (tmp != ptr)
        {
            tmp = tmp->next;
        }
        predloz* nxt = tmp->next;
        tmp->next = new_el;
        new_el = nxt;
        tmp = tmp->next;
        tmp->next = new_el;
    }
    else
        tmp->next = new_el;
}*/

/*predloz* vvod(predloz *head, predloz *ptr)
{
    if (head == NULL)
    {
        head = (predloz *)malloc(sizeof(predloz));
        head = create_node();
        ptr = head;
    }
    else
    {
        if (ptr->next_slovo == NULL)
        {
            ptr->next_slovo = create_node();
        }
        else
        {
            predloz *tmp_predl = head->next_slovo;
            ptr->next_slovo = create_node();
            ptr->next_slovo->next_slovo = tmp_predl;
        }
    }
}
*/
predloz *menu1()
{
    predloz *head = (predloz *)malloc(sizeof(predloz));
    head = NULL;
    int num;
    predloz *ptr = head;
    predloz *show = NULL;
    system("clear");
    while (1)
    {
        printf("Menu\n");
        printf("1-Clear\n");
        printf("2-Pust or not\n");
        printf("3-Uk na start\n");
        printf("4-Uk end?\n");
        printf("5-Uk vpered\n");
        printf("6-Vzyat elem za ukaz\n");
        printf("7-Delete elem za uk\n");
        printf("8-Show elem za uk\n");
        printf("9-Change elem\n");
        printf("10-Add elem\n");
        printf("11-Raspechat struct\n");
        printf("12-Zakonch spisok\n");

        printf("Vvedite znach: ");
        scanf("%d", &num);

        switch (num)
        {
        case 1:
            system("clear");
            if (head == NULL)
                printf("Spisok pust\n");
            else
                head = clear_1(head);
            break;

        case 2:
            if (check_pust(head))
            {
                print_spisok(head, ptr);
            }
            break;

        case 3:
            system("clear");
            if (head == NULL)
                printf("Spisok pust\n");
            else
            {
                ptr = set_start(head);
                print_spisok(head, ptr);
            }

            break;

        case 4:
            system("clear");
            if (head == NULL)
                printf("Spisok pust\n");
            else
            {
                print_spisok(head, ptr);
                check_end(ptr);
            }
            break;

        case 5:
            system("clear");
            if (head == NULL)
                printf("Spisok pust\n");
            else
                ptr = go_next(head, ptr);
            break;

        case 6:
            system("clear");
            if (head == NULL)
                printf("Spisok pust\n");
            else
            {
                show = pokaz_elem(head, ptr);
                print_spisok(head, ptr);
                show->next_slovo = NULL;
                print_spisok(show, ptr);
                if (show == NULL)
                {
                    print_spisok(head, ptr);
                    printf("Not next elem!\n");
                }
            }
            break;

        case 7:
            system("clear");
            if (head == NULL)
                printf("Spisok pust\n");
            else
                remove_elem(head, ptr);

            break;

        case 8:
            system("clear");
            if (head == NULL)
                printf("Spisok pust\n");
            else
            {
                // elem = get_elem(head, ptr);
                if (get_elem(head, ptr) != NULL)
                {
                    print_spisok(head, ptr);
                    vyvod_elementa(get_elem(head, ptr));
                }
            }

            break;

        case 9:
            system("clear");
            if (head == NULL)
                printf("Spisok pust\n");
            else
                change_elem(head, ptr);
            break;

        case 10:
            system("clear");
            if (head == NULL)
            {
                head = (predloz *)malloc(sizeof(predloz));
                head = create_node();
                ptr = head;
            }
            else
            {
                if (ptr->next_slovo == NULL)
                {
                    ptr->next_slovo = create_node();
                }
                else
                {
                    predloz *tmp_predl = head->next_slovo;
                    ptr->next_slovo = create_node();
                    ptr->next_slovo->next_slovo = tmp_predl;
                }
            }
            print_spisok(head, ptr);
            break;

        case 11:
            system("clear");
            if (head == NULL)
                printf("Spisok pust\n");
            else
                print_spisok(head, ptr);
            break;

        case 12:
            system("clear");
            if (head == NULL)
            {
                printf("the offer is empty, there is nothing to return\n");
                break;
            }
            return head;
            break;
        default:
            printf("Vvedeno ne to znach, try again!\n");

            // system("clear");
        }
    }
}

predloz *menu2(predloz* head)
{
    // predloz *head = (predloz *)malloc(sizeof(predloz));
    // head = NULL;
    int num;
    predloz *ptr = head;
    predloz *show = NULL;
    system("clear");
    while (1)
    {
        printf("Menu\n");
        printf("1-Clear\n");
        printf("2-Pust or not\n");
        printf("3-Uk na start\n");
        printf("4-Uk end?\n");
        printf("5-Uk vpered\n");
        printf("6-Vzyat elem za ukaz\n");
        printf("7-Delete elem za uk\n");
        printf("8-Show elem za uk\n");
        printf("9-Change elem\n");
        printf("10-Add elem\n");
        printf("11-Raspechat struct\n");
        printf("12-Zakonch spisok\n");

        printf("Vvedite znach: ");
        scanf("%d", &num);

        switch (num)
        {
        case 1:
            system("clear");
            if (head == NULL)
                printf("Spisok pust\n");
            else
                head = clear_1(head);
            break;

        case 2:
            if (check_pust(head))
            {
                print_spisok(head, ptr);
            }
            break;

        case 3:
            system("clear");
            if (head == NULL)
                printf("Spisok pust\n");
            else
            {
                ptr = set_start(head);
                print_spisok(head, ptr);
            }

            break;

        case 4:
            system("clear");
            if (head == NULL)
                printf("Spisok pust\n");
            else
            {
                print_spisok(head, ptr);
                check_end(ptr);
            }
            break;

        case 5:
            system("clear");
            if (head == NULL)
                printf("Spisok pust\n");
            else
                ptr = go_next(head, ptr);
            break;

        case 6:
            system("clear");
            if (head == NULL)
                printf("Spisok pust\n");
            else
            {
                show = pokaz_elem(head, ptr);
                print_spisok(head, ptr);
                show->next_slovo = NULL;
                print_spisok(show, ptr);
                if (show == NULL)
                {
                    print_spisok(head, ptr);
                    printf("Not next elem!\n");
                }
            }
            break;

        case 7:
            system("clear");
            if (head == NULL)
                printf("Spisok pust\n");
            else
                remove_elem(head, ptr);

            break;

        case 8:
            system("clear");
            if (head == NULL)
                printf("Spisok pust\n");
            else
            {
                // elem = get_elem(head, ptr);
                if (get_elem(head, ptr) != NULL)
                {
                    print_spisok(head, ptr);
                    vyvod_elementa(get_elem(head, ptr));
                }
            }

            break;

        case 9:
            system("clear");
            if (head == NULL)
                printf("Spisok pust\n");
            else
                change_elem(head, ptr);
            break;

        case 10:
            system("clear");
            if (head == NULL)
            {
                head = (predloz *)malloc(sizeof(predloz));
                head = create_node();
                ptr = head;
            }
            else
            {
                if (ptr->next_slovo == NULL)
                {
                    ptr->next_slovo = create_node();
                }
                else
                {
                    predloz *tmp_predl = head->next_slovo;
                    ptr->next_slovo = create_node();
                    ptr->next_slovo->next_slovo = tmp_predl;
                }
            }
            print_spisok(head, ptr);
            break;

        case 11:
            system("clear");
            if (head == NULL)
                printf("Spisok pust\n");
            else
                print_spisok(head, ptr);
            break;

        case 12:
            system("clear");
            if (head == NULL)
            {
                printf("the offer is empty, there is nothing to return\n");
                break;
            }
            return head;
            break;
        default:
            printf("Vvedeno ne to znach, try again!\n");

            // system("clear");
        }
    }
}

ochered *create_ochered()
{
    ochered *ocher = (ochered *)malloc(sizeof(ochered));
    ocher->size = 0;
    ocher->first = NULL;
    ocher->last = NULL;
    return ocher;
}

void add_to_end(ochered *ocher)
{
    if (ocher->first == NULL)
    {
        text *tmp_text = (text *)malloc(sizeof(text));
        tmp_text->predl = menu1();
        tmp_text->next_predl = NULL;
        ocher->size++;
        ocher->first = tmp_text;
        ocher->last = tmp_text;
    }
    else
    {
        text *tmp_text = (text *)malloc(sizeof(text));
        tmp_text->predl = menu1();
        tmp_text->next_predl = NULL;
        ocher->last->next_predl = tmp_text;
        ocher->last = tmp_text;
        ocher->size++;
    }
    return;
}

void print_spisok_ochered(predloz *head)
{
    int i;
    while (head != NULL)
    {

        for (i = 0; head->slovo[i] != '\n'; i++)
            printf("%c", head->slovo[i]);
        printf(" ");
        head = head->next_slovo;
    }
    printf("\n");
    return;
}

void print_ochered(ochered *ocher)
{
    system("clear");
    if (!ocher->first)
        printf("the queue is empty\n");
    text *tmp_text = ocher->first;
    while (tmp_text)
    {
        print_spisok_ochered(tmp_text->predl);
        tmp_text = tmp_text->next_predl;
    }
    return;
}

void pust_or_not_ocher(ochered *ocher)
{
    system("clear");
    if (!ocher->first)
        printf("Еhe queue is empty\n");
    else
        printf("Еhe queue is not empty\n");
    return;
}

void show_start_elem(ochered *ocher)
{
    system("clear");
    if (!ocher->first)
        printf("the queue is empty\n");
    else
        print_spisok_ochered(ocher->first->predl);
    return;
}

void del_start_ochered(ochered *ocher)
{
    if (!ocher->first)
    {
        printf("the queue is empty\n");
        return;
    }
    text *tmp_text;
    if (ocher->first == ocher->last)
    {
        tmp_text = ocher->first;
        ocher->first = NULL;
        ocher->last = NULL;
        clear_1(tmp_text->predl);
        free(tmp_text);
    }
    else
    {
        tmp_text = ocher->first;
        ocher->first = ocher->first->next_predl;
        clear_1(tmp_text->predl);
        free(tmp_text);
    }
    return;
}

void get_elem_start_ocher(ochered *ocher)
{
    if (!ocher->first)
    {
        printf("the queue is empty\n");
        return;
    }
    text *tmp_text;
    if (ocher->first == ocher->last)
    {
        tmp_text = ocher->first;
        ocher->first = NULL;
        ocher->last = NULL;
        print_spisok_ochered(tmp_text->predl);
        clear_1(tmp_text->predl);
        free(tmp_text);
    }
    else
    {
        tmp_text = ocher->first;
        ocher->first = ocher->first->next_predl;
        print_spisok_ochered(tmp_text->predl);
        clear_1(tmp_text->predl);
        free(tmp_text);
    }
    return;
}

void clear_ocher(ochered *ocher)
{
    if (!ocher->first)
    {
        printf("the queue is empty\n");
        return;
    }
    while (ocher->first)
    {
        del_start_ochered(ocher);
    }
    return;
}

void change_elem_start_ocher(ochered *ocher)
{
    if (!ocher->first)
    {
        printf("the queue is empty\n");
        return;
    }
    //clear_1(ocher->first->predl);
    ocher->first->predl = menu2(ocher->first->predl);
    return;
}

void menu(ochered *ocher)
{

    while (1)
    {
        int num1;
        printf("Menu\n");
        printf("1-Clear\n");
        printf("2-Pust or not\n");
        printf("3-Show start elem\n");
        printf("4-Delete start\n");
        printf("5-Get elem from start\n");
        printf("6-Change elem from start\n");
        printf("7-Add elem to the end\n");
        printf("8-Print ochered\n");
        printf("9-Zakoncit ochered\n");

        printf("Vvedite znach: ");
        scanf("%d", &num1);

        switch (num1)
        {
        case 1:
            clear_ocher(ocher);
            break;
        case 2:
            pust_or_not_ocher(ocher);
            break;
        case 3:
            show_start_elem(ocher);
            break;
        case 4:
            del_start_ochered(ocher);
            break;
        case 5:
            get_elem_start_ocher(ocher);
            break;
        case 6:
            change_elem_start_ocher(ocher);
            break;
        case 7:
            add_to_end(ocher);
            break;
        case 8:
            print_ochered(ocher);
            break;
        case 9:
            clear_ocher(ocher);
            return;
            break;

        default:
            printf("Vvedeno ne to znach, try again!\n");

            // system("clear");
        }
    }
}

/*void print_predl(predloz *top_predl)
{
    predloz *tmp_predl = top_predl;
    while (tmp_predl != NULL)
    {
        printf("%s ", tmp_predl->slovo);
        tmp_predl = tmp_predl->next_slovo;
    }
    printf("\n");
    return;
}*/

int main()
{
    ochered *ocher = create_ochered();
    menu(ocher);
    // predloz *top_predl = create_predloz();
    // print_predl(top_predl);
    
    return 0;
}