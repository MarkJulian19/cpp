/*
ДЗ-1. Срок сдачи — до 29.02.23
Использование STL и типа string запрещено.
Определить класс с полями разных типов, среди которых обязательно должны быть указатели. Класс должен быть АТД — все поля-данные закрыты. Будет использоваться в п.2.
Для этого класса написать конструкторы, деструктор, оператор присваивания и произвольную функцию-член класса. В каждую из специальных функций класса включить отладочный вывод на экран, чтобы было понятно, какая функция работает.
Это примеры данных, которые будут помещаться в список (см. п.2), вы можете написать свои:
Элемент данных - объект, содержащий информацию о клиенте: фамилия, время добавления в очередь (целое или строка). Хранится также информация о текущем количестве клиентов в списке и об общем количестве клиентов во всех списках.
Элемент данных – объект, содержащий информацию о заказе: название фирмы, номер телефона (целое или строка), номер заказа. Нумерация заказов единая для всех списков.
Элемент данных – объект «банковский счет». Необходимые члены-данные: номер счета, владелец счета, дата создания счета (число или строка), сумма денег, которая на нем хранится. Нумерация счетов единая для всех списков.
2. АТД. Список данных.
Класс — список (двунаправленный), в качестве элемента данных использовать тип, определенный в п.1.
Класс список должен быть написан так, чтобы его легко было потом адаптировать для работы с данными произвольного типа.
Определить необходимые конструкторы.
Обеспечить корректное уничтожение объектов.
В классе должны быть функции:
добавления элемента в начало (push_front) и в конец (push_back),+
чтение первого элемента списка (front),+
чтение последнего элемента списка (back),+
удаление первого элемента списка (pop_front),+
удаление последнего элемента списка (pop_back),+
добавление элемента x перед позицией p ( insert(p,x)),+
удаление элемента из позиции p (erase(p))+
проверка списка на пустоту (empty),+
текущее число элементов (size),+
вывод информации об элементах списка (print).+
Функция main должна демонстрировать работу с объектами данного класса.
Пример работы: Date d1(…); List l1; l1.push_front(d1); ... l1.print(); и т. д.
*/

#include <iostream>
#include <cstring>
#define prin_t 3 // 1-конструктор или диструктор
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

    void operator=(bank_account &b_a)
    {
        account_holder = new char[strlen(b_a.account_holder) + 1];
        strcpy(account_holder, b_a.account_holder);
        date_of_creation_unix_time = b_a.date_of_creation_unix_time;
        money = b_a.money;
        id = b_a.id;
        if ((prin_t == 1) or (prin_t == 3))
            cout << "void operator=(bank_account &b_a)" << endl;
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

template <typename Type>
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

    void size()
    {
        cout << list_size << endl;
        if ((prin_t == 2) or (prin_t == 3))
            cout << "void size()" << endl;
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

int main()
{
    const char *tmp_str1 = "hallo1\0";
    const char *tmp_str2 = "hallo2\0";
    const char *tmp_str3 = "hallo3\0";
    const char *tmp_str4 = "hallo4\0";

    bank_account acc1(tmp_str1, 10000, 12345346);
    bank_account acc2(tmp_str2, 20000, -1234);
    bank_account acc3(tmp_str3, 234567, 1234432);
    bank_account acc4(tmp_str4, 265432, -34);
    cout << acc4.get_id() << endl;
    info_list<bank_account> a1;

    a1.print();

    a1.push_front(acc3);
    a1.push_front(acc4);

    a1.print();

    a1.push_back(acc1);

    a1.print();

    a1.front();

    a1.back();

    a1.size();

    a1.empty();

    a1.insert(2, acc2);

    a1.print();

    a1.erase(2);
    a1.print();
    a1.pop_back();
    a1.print();
    a1.pop_front();
    a1.print();
    return 0;
}