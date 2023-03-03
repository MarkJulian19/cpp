#include <iostream>
#include <cstring>
#define prin_t 0 // 1-конструктор или диструктор
                 // 2-иные функции
                 // 3- 1 и 2
using namespace std;

class bank_account
{
    char *account_holder;
    unsigned int date_of_creation_unix_time;
    long long money;
    unsigned int id;
    static unsigned int id_counter;

public:
    //--------------------------------------------------------------------------------
    // конструкторы, деструкторы
    bank_account()
    {
        account_holder = NULL;
        date_of_creation_unix_time = 0;
        money = 0;
        id = id_counter;
        id_counter++;
        if ((prin_t == 1) or (prin_t == 3))
            cout << "bank_account()" << endl;
    };

    bank_account(const char *a_h, unsigned int d_o_c_u_t, long long m)
    {
        account_holder = new char[strlen(a_h) + 1];
        strcpy(account_holder, a_h);
        date_of_creation_unix_time = d_o_c_u_t;
        money = m;
        id = id_counter;
        id_counter++;
        if ((prin_t == 1) or (prin_t == 3))
            cout << "bank_account(char *a_h, unsigned int d_o_c_u_t, long long m)" << endl;
    };

    bank_account(bank_account &b_a)
    {
        account_holder = new char[strlen(b_a.account_holder) + 1];
        strcpy(account_holder, b_a.account_holder);
        date_of_creation_unix_time = b_a.date_of_creation_unix_time;
        money = b_a.money;
        id = b_a.id;
        if ((prin_t == 1) or (prin_t == 3))
            cout << "bank_account(bank_account &b_a)" << endl;
    };

    ~bank_account()
    {
        delete[] account_holder;
        if ((prin_t == 1) or (prin_t == 3))
            cout << "~bank_account()" << endl;
    };
    //--------------------------------------------------------------------------------

    unsigned int get_id()
    {
        if ((prin_t == 2) or (prin_t == 3))
            cout << "unsigned int get_id()" << endl;
        return id;
    }

    const char *get_account_holder()
    {
        if ((prin_t == 2) or (prin_t == 3))
            cout << "char *get_account_holder()" << endl;
        return account_holder;
    };

    unsigned int get_date_of_creation_unix_time()
    {
        if ((prin_t == 2) or (prin_t == 3))
            cout << "unsigned int get_date_of_creation_unix_time()" << endl;
        return date_of_creation_unix_time;
    };

    long long get_money()
    {
        if ((prin_t == 2) or (prin_t == 3))
            cout << "long long get_money()" << endl;
        return money;
    }

    bank_account &operator=(bank_account &b_a)
    {
        if (this == &b_a)
            return *this;
        delete[] this->account_holder;
        account_holder = new char[strlen(b_a.account_holder) + 1];
        strcpy(account_holder, b_a.account_holder);
        date_of_creation_unix_time = b_a.date_of_creation_unix_time;
        money = b_a.money;
        id = b_a.id;
        if ((prin_t == 1) or (prin_t == 3))
            cout << "void operator=(bank_account &b_a)" << endl;
        return *this;
    }

    void print_inf()
    {
        cout << "id: " << id << endl;
        cout << "account_holder: " << account_holder << endl;
        cout << "date_of_creation_unix_time: " << date_of_creation_unix_time << endl;
        cout << "money: " << money << endl;
        cout << endl;
        if ((prin_t == 2) or (prin_t == 3))
            cout << "void print_inf()" << endl;
        return;
    }
};

unsigned int bank_account::id_counter = 1;

template <class Type>
class info_list
{
    struct Node
    {
        Node *next;
        Node *prev;
        Type inf;
    };
    Node *head, *tail;
    unsigned int list_size;
    // static unsigned int id_counter;

public:
    //--------------------------------------------------------------------------------
    // конструкторы, деструкторы

    info_list()
    {
        head = NULL;
        tail = NULL;
        list_size = 0;
        if ((prin_t == 1) or (prin_t == 3))
            cout << "info_list()" << endl;
    };

    ~info_list()
    {
        Node *tmp;
        while (head != NULL)
        {
            tmp = head->next;
            delete head;
            head = tmp;
        }
        if ((prin_t == 1) or (prin_t == 3))
            cout << "~info_list()" << endl;
    };
    //--------------------------------------------------------------------------------

    void push_front(Type b_a)
    {
        if (head == NULL)
        {
            head = new Node;
            head->next = NULL;
            head->prev = NULL;
            head->inf = b_a;
            tail = head;
            list_size++;
        }
        else
        {
            Node *tmp = new Node;
            tmp->inf = b_a;
            tmp->prev = NULL;
            tmp->next = head;
            head->prev = tmp;
            head = tmp;
            list_size++;
        }
        if ((prin_t == 2) or (prin_t == 3))
            cout << "void push_front(Type b_a)" << endl;
    };

    void push_back(Type b_a)
    {
        if (head == NULL)
        {
            head = new Node;
            head->next = NULL;
            head->prev = NULL;
            head->inf = b_a;
            tail = head;
            list_size++;
        }
        else
        {
            Node *tmp = new Node;
            tmp->inf = b_a;
            tmp->next = NULL;
            tmp->prev = tail;
            tail->next = tmp;
            tail = tmp;
            list_size++;
        }
        if ((prin_t == 2) or (prin_t == 3))
            cout << "void push_back(Type b_a)" << endl;
    };

    void insert(unsigned int p, Type b_a) // НУМЕРАЦИЯ С 1
    {
        if (p > list_size)
        {
            cout << "ERROR: p > list_size <=> " << p << " > " << list_size << endl;
            if ((prin_t == 2) or (prin_t == 3))
                cout << "void insert(unsigned int p, Type b_a) " << endl;
            return;
        }
        unsigned int i = 1;
        Node *tmp = head;
        while (i < p)
        {
            tmp = tmp->next;
            i++;
        }
        Node *tmp1 = new Node;
        tmp1->next = tmp;
        tmp1->prev = tmp->prev;
        tmp1->inf = b_a;
        tmp->prev->next = tmp1;
        tmp->prev = tmp1;
        list_size++;
        if ((prin_t == 2) or (prin_t == 3))
            cout << "void insert(unsigned int p, Type b_a) " << endl;
    };

    void erase(unsigned int p) // НУМЕРАЦИЯ С 1
    {
        if ((p > list_size) or (p == 0))
        {
            cout << "ERROR: p > list_size <=> " << p << " > " << list_size << endl;
            if ((prin_t == 2) or (prin_t == 3))
                cout << "void erase(unsigned int p)" << endl;
            return;
        }
        unsigned int i = 1;
        Node *tmp = head;
        while (i < p)
        {
            tmp = tmp->next;
            i++;
        }
        if ((tmp->next == NULL) and (tmp->prev == NULL))
        {
            head = NULL;
            tail = NULL;
            cout << "Data of the deleted account:" << endl;
            cout << "------------------------------------------------------------------------------" << endl;
            tmp->inf.print_inf();
            cout << "------------------------------------------------------------------------------" << endl;
            delete tmp;
            list_size--;
            if ((prin_t == 2) or (prin_t == 3))
                cout << "void erase(unsigned int p)" << endl;
            return;
        }
        if (tmp->prev)
        {
            tmp->prev->next = tmp->next;
        }
        else
        {
            tmp->next->prev = NULL;
            head = tmp->next;
        }
        if (tmp->next)
        {
            tmp->next->prev = tmp->prev;
        }
        else
        {
            tmp->prev->next = NULL;
            tail = tmp->prev;
        }
        cout << "Data of the deleted account:" << endl;
        cout << "------------------------------------------------------------------------------" << endl;
        tmp->inf.print_inf();
        cout << "------------------------------------------------------------------------------" << endl;
        delete tmp;
        list_size--;
        if ((prin_t == 2) or (prin_t == 3))
            cout << "void erase(unsigned int p)" << endl;
    };

    void front()
    {
        if (head != NULL)
        {
            head->inf.print_inf();
        }
        else
        {
            cout << "head = NULL" << endl;
        }
        if ((prin_t == 2) or (prin_t == 3))
            cout << "void front()" << endl;
    };

    void back()
    {
        if (tail != NULL)
        {
            tail->inf.print_inf();
        }
        else
        {
            cout << "tail = NULL" << endl;
        }
        if ((prin_t == 2) or (prin_t == 3))
            cout << "void back()" << endl;
    };

    unsigned int size()
    {
        // cout << list_size << endl;
        if ((prin_t == 2) or (prin_t == 3))
            cout << "void size()" << endl;
        return list_size;
    };

    void empty()
    {
        if (list_size)
            cout << "The list is not empty" << endl;
        else
            cout << "The list is empty" << endl;
        if ((prin_t == 2) or (prin_t == 3))
            cout << "void empty()" << endl;
    };

    void print()
    {
        if (list_size)
        {
            Node *tmp = head;
            cout << "\nInformation about all clients of this database:" << endl;
            cout << "------------------------------------------------------------------------------" << endl;
            while (tmp)
            {
                tmp->inf.print_inf();
                tmp = tmp->next;
            }
            cout << "------------------------------------------------------------------------------" << endl;
        }
        else
            cout << "The list is empty" << endl;
        if ((prin_t == 2) or (prin_t == 3))
            cout << "void print()" << endl;
    };

    void pop_front()
    {
        if (head)
        {
            Node *tmp = head;
            if ((tmp->next == NULL) and (tmp->prev == NULL))
            {
                head = NULL;
                tail = NULL;
                cout << "Data of the deleted account:" << endl;
                cout << "------------------------------------------------------------------------------" << endl;
                tmp->inf.print_inf();
                cout << "------------------------------------------------------------------------------" << endl;
                delete tmp;
                list_size--;
                if ((prin_t == 2) or (prin_t == 3))
                    cout << "void pop_front()" << endl;
                return;
            }
            head = head->next;
            head->prev = NULL;
            cout << "Data of the deleted account:" << endl;
            cout << "------------------------------------------------------------------------------" << endl;
            tmp->inf.print_inf();
            cout << "------------------------------------------------------------------------------" << endl;
            delete tmp;
            list_size--;
        }
        else
        {
            cout << "The list is empty" << endl;
        }
        if ((prin_t == 2) or (prin_t == 3))
            cout << "void pop_front()" << endl;
    };

    void pop_back()
    {
        if (tail)
        {
            Node *tmp = tail;
            if ((tmp->next == NULL) and (tmp->prev == NULL))
            {
                head = NULL;
                tail = NULL;
                cout << "Data of the deleted account:" << endl;
                cout << "------------------------------------------------------------------------------" << endl;
                tmp->inf.print_inf();
                cout << "------------------------------------------------------------------------------" << endl;
                delete tmp;
                list_size--;
                if ((prin_t == 2) or (prin_t == 3))
                    cout << "void pop_back()" << endl;
                return;
            }
            tail = tail->prev;
            tail->next = NULL;
            cout << "Data of the deleted account:" << endl;
            cout << "------------------------------------------------------------------------------" << endl;
            tmp->inf.print_inf();
            cout << "------------------------------------------------------------------------------" << endl;
            delete tmp;
            list_size--;
        }
        else
        {
            cout << "The list is empty" << endl;
        }
        if ((prin_t == 2) or (prin_t == 3))
            cout << "void pop_front()" << endl;
    };
};
