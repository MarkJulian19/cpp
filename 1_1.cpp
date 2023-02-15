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
#define prin_t 0
using namespace std;

class bank_account
{
    bank_account *prev, *next;
    // int account_number;
    char *account_holder;
    unsigned int date_of_creation_unix_time;
    long long money;
    unsigned int id;

public:
    //--------------------------------------------------------------------------------
    // конструкторы, деструкторы
    bank_account()
    {
        prev = NULL;
        next = NULL;
        account_holder = NULL;
        date_of_creation_unix_time = 0;
        money = 0;
        id = 0;
        if (prin_t)
            cout << "bank_account()" << endl;
    };

    bank_account(char *a_h, unsigned int d_o_c_u_t, long long m)
    {
        prev = NULL;
        next = NULL;
        account_holder = new char[strlen(a_h) + 1];
        strcpy(account_holder, a_h);
        date_of_creation_unix_time = d_o_c_u_t;
        money = m;
        id = 0;
        if (prin_t)
            cout << "bank_account(char *a_h, unsigned int d_o_c_u_t, long long m)" << endl;
    };

    bank_account(bank_account &b_a)
    {
        prev = b_a.prev;
        next = b_a.next;
        account_holder = new char[strlen(b_a.account_holder) + 1];
        strcpy(account_holder, b_a.account_holder);
        date_of_creation_unix_time = b_a.date_of_creation_unix_time;
        money = b_a.money;
        id = b_a.id;
        if (prin_t)
            cout << "bank_account(bank_account &b_a)" << endl;
    };

    ~bank_account()
    {
        // cout << account_holder << endl;
        delete[] account_holder;
        if (prin_t)
            cout << "~bank_account()" << endl;
    };
    //--------------------------------------------------------------------------------

    void set_id(unsigned int a)
    {
        id = a;
    }
    unsigned int get_id()
    {
        return id;
    }

    bank_account *get_next()
    {
        if (prin_t)
            cout << "bank_account get_next()" << endl;
        return next;
    };

    bank_account *get_prev()
    {
        if (prin_t)
            cout << "bank_account get_prev()" << endl;
        return prev;
    };

    void set_prev(bank_account *p)
    {
        prev = p;
        if (prin_t)
            cout << "void set_prev(bank_account *p)" << endl;
    };

    void set_next(bank_account *p)
    {
        next = p;
        if (prin_t)
            cout << "void set_next(bank_account *p)" << endl;
    };

    char *get_account_holder()
    {
        if (prin_t)
            cout << "char *get_account_holder()" << endl;
        return account_holder;
    };

    unsigned int get_date_of_creation_unix_time()
    {
        if (prin_t)
            cout << "unsigned int get_date_of_creation_unix_time()" << endl;
        return date_of_creation_unix_time;
    };

    long long get_money()
    {
        if (prin_t)
            cout << "long long get_money()" << endl;
        return money;
    }
};

class info_list
{
    bank_account *head, *tail;
    unsigned int list_size;
    static unsigned int id_counter;

public:
    //--------------------------------------------------------------------------------
    // конструкторы, деструкторы

    info_list()
    {
        head = NULL;
        tail = NULL;
        list_size = 0;
        if (prin_t)
            cout << "info_list()" << endl;
    };

    ~info_list()
    {
        bank_account *tmp;
        while (head != NULL)
        {
            // tmp = tmp->get_next();
            // delete[] head;
            // head = tmp;
            tmp = head->get_next();
            delete head;
            head = tmp;
        }
        if (prin_t)
            cout << "~info_list()" << endl;
    };
    //--------------------------------------------------------------------------------
    void list_size_add()
    {
        list_size++;
    };

    void list_size_sub()
    {
        list_size--;
    };

    void push_front(bank_account b_a)
    {
        if (head == NULL)
        {
            head = new bank_account(b_a);
            head->set_next(NULL);
            head->set_prev(NULL);
            head->set_id(id_counter);
            id_counter++;
            tail = head;
            list_size_add();
        }
        else
        {
            bank_account *tmp = new bank_account(b_a);
            tmp->set_prev(NULL);
            tmp->set_next(head);
            head->set_prev(tmp);
            tmp->set_id(id_counter);
            id_counter++;
            head = tmp;
            list_size_add();
        }
        if (prin_t)
            cout << "void push_front(bank_account b_a)" << endl;
    };

    void push_back(bank_account b_a)
    {
        if (head == NULL)
        {
            head = new bank_account(b_a);
            head->set_next(NULL);
            head->set_prev(NULL);
            head->set_id(id_counter);
            id_counter++;
            tail = head;
            list_size_add();
        }
        else
        {
            // cout << "--------------------" << endl;
            bank_account *tmp = new bank_account(b_a);
            tmp->set_prev(tail);
            tmp->set_next(NULL);
            tail->set_next(tmp);
            tmp->set_id(id_counter);
            id_counter++;
            tail = tmp;
            list_size_add();
        }
        if (prin_t)
            cout << "void push_back(bank_account b_a)" << endl;
    };

    void insert(unsigned int p, bank_account x) // НУМЕРАЦИЯ С 1
    {
        if (p > list_size)
        {
            cout << "ERROR: p > list_size <=> " << p << " > " << list_size << endl;
            return;
        }
        unsigned int i = 1;
        bank_account *tmp = head;
        while (i < p)
        {
            tmp = tmp->get_next();
            i++;
        }
        bank_account *tmp1 = new bank_account(x);
        tmp1->set_next(tmp);
        tmp1->set_prev(tmp->get_prev());
        tmp1->set_id(id_counter);
        id_counter++;
        tmp->get_prev()->set_next(tmp1);
        tmp->set_prev(tmp1);
        list_size_add();
    };

    void erase(unsigned int p) // НУМЕРАЦИЯ С 1
    {
        if ((p > list_size) or (p == 0))
        {
            cout << "ERROR: p > list_size <=> " << p << " > " << list_size << endl;
            return;
        }
        unsigned int i = 1;
        bank_account *tmp = head;
        while (i < p)
        {
            tmp = tmp->get_next();
            i++;
        }
        if ((tmp->get_next() == NULL) and (tmp->get_prev() == NULL))
        {
            head = NULL;
            tail = NULL;
            cout << "Data of the deleted account:" << endl;
            cout << "------------------------------------------------------------------------------" << endl;
            cout << "id: " << tmp->get_id() << endl;
            cout << "account_holder: " << tmp->get_account_holder() << endl;
            cout << "date_of_creation_unix_time: " << tmp->get_date_of_creation_unix_time() << endl;
            cout << "money: " << tmp->get_money() << endl;
            cout << endl;
            cout << "------------------------------------------------------------------------------" << endl;
            delete tmp;
            list_size_sub();
            return;
        }
        if (tmp->get_prev())
        {
            tmp->get_prev()->set_next(tmp->get_next());
        }
        else
        {
            tmp->get_next()->set_prev(NULL);
            head = tmp->get_next();
        }
        if (tmp->get_next())
        {
            tmp->get_next()->set_prev(tmp->get_prev());
        }
        else
        {
            tmp->get_prev()->set_next(NULL);
            tail = tmp->get_prev();
        }
        cout << "Data of the deleted account:" << endl;
        cout << "------------------------------------------------------------------------------" << endl;
        cout << "id: " << tmp->get_id() << endl;
        cout << "account_holder: " << tmp->get_account_holder() << endl;
        cout << "date_of_creation_unix_time: " << tmp->get_date_of_creation_unix_time() << endl;
        cout << "money: " << tmp->get_money() << endl;
        cout << endl;
        cout << "------------------------------------------------------------------------------" << endl;
        delete tmp;
        list_size_sub();
    };

    void front()
    {
        if (head != NULL)
        {
            cout << head->get_account_holder() << endl;
        }
        else
        {
            cout << "head = NULL" << endl;
        }
        if (prin_t)
            cout << "void front()" << endl;
    };

    void back()
    {
        if (tail != NULL)
        {
            cout << tail->get_account_holder() << endl;
        }
        else
        {
            cout << "tail = NULL" << endl;
        }
        if (prin_t)
            cout << "void back()" << endl;
    };

    void size()
    {
        cout << list_size << endl;
        if (prin_t)
            cout << "void size()" << endl;
    };

    void empty()
    {
        if (list_size)
            cout << "The list is not empty" << endl;
        else
            cout << "The list is empty" << endl;
        if (prin_t)
            cout << "void empty()" << endl;
    };

    void print()
    {
        if (list_size)
        {
            bank_account *tmp = head;
            cout << "\ninformation about all clients of this database:" << endl;
            cout << "------------------------------------------------------------------------------" << endl;
            while (tmp)
            {
                cout << "id: " << tmp->get_id() << endl;
                cout << "account_holder: " << tmp->get_account_holder() << endl;
                cout << "date_of_creation_unix_time: " << tmp->get_date_of_creation_unix_time() << endl;
                cout << "money: " << tmp->get_money() << endl;
                cout << endl;
                tmp = tmp->get_next();
            }
            cout << "------------------------------------------------------------------------------" << endl;
        }
        else
            cout << "The list is empty" << endl;
        if (prin_t)
            cout << "void print()" << endl;
    };

    void pop_front()
    {
        if (head)
        {
            bank_account *tmp = head;
            if ((tmp->get_next() == NULL) and (tmp->get_prev() == NULL))
            {
                head = NULL;
                tail = NULL;
                cout << "Data of the deleted account:" << endl;
                cout << "------------------------------------------------------------------------------" << endl;
                cout << "id: " << tmp->get_id() << endl;
                cout << "account_holder: " << tmp->get_account_holder() << endl;
                cout << "date_of_creation_unix_time: " << tmp->get_date_of_creation_unix_time() << endl;
                cout << "money: " << tmp->get_money() << endl;
                cout << endl;
                cout << "------------------------------------------------------------------------------" << endl;
                delete tmp;
                list_size_sub();
                return;
            }
            head = head->get_next();
            head->set_prev(NULL);
            cout << "Data of the deleted account:" << endl;
            cout << "------------------------------------------------------------------------------" << endl;
            cout << "id: " << tmp->get_id() << endl;
            cout << "account_holder: " << tmp->get_account_holder() << endl;
            cout << "date_of_creation_unix_time: " << tmp->get_date_of_creation_unix_time() << endl;
            cout << "money: " << tmp->get_money() << endl;
            cout << endl;
            cout << "------------------------------------------------------------------------------" << endl;
            delete tmp;
            list_size_sub();
        }
        else
        {
            cout << "The list is empty" << endl;
        }
        if (prin_t)
            cout << "void pop_front()" << endl;
    };

    void pop_back()
    {
        if (tail)
        {
            bank_account *tmp = tail;
            if ((tmp->get_next() == NULL) and (tmp->get_prev() == NULL))
            {
                head = NULL;
                tail = NULL;
                cout << "Data of the deleted account:" << endl;
                cout << "------------------------------------------------------------------------------" << endl;
                cout << "id: " << tmp->get_id() << endl;
                cout << "account_holder: " << tmp->get_account_holder() << endl;
                cout << "date_of_creation_unix_time: " << tmp->get_date_of_creation_unix_time() << endl;
                cout << "money: " << tmp->get_money() << endl;
                cout << endl;
                cout << "------------------------------------------------------------------------------" << endl;
                delete tmp;
                list_size_sub();
                return;
            }
            tail = tail->get_prev();
            tail->set_next(NULL);
            cout << "Data of the deleted account:" << endl;
            cout << "------------------------------------------------------------------------------" << endl;
            cout << "id: " << tmp->get_id() << endl;
            cout << "account_holder: " << tmp->get_account_holder() << endl;
            cout << "date_of_creation_unix_time: " << tmp->get_date_of_creation_unix_time() << endl;
            cout << "money: " << tmp->get_money() << endl;
            cout << endl;
            cout << "------------------------------------------------------------------------------" << endl;
            delete tmp;
            list_size_sub();
        }
        else
        {
            cout << "The list is empty" << endl;
        }
        if (prin_t)
            cout << "void pop_front()" << endl;
    };
};

unsigned int info_list::id_counter = 1;

int main()
{
    const char *tmp_str = "hallo\0";
    char *str = new char[6];
    strcpy(str, tmp_str);
    bank_account acc1(str, 1, 1234);
    bank_account acc2(str, 2, 1234);
    info_list l1;
    l1.push_front(acc1);
    l1.push_front(acc2);
    l1.print();
    l1.erase(1);
    l1.print();
    l1.pop_front();
    l1.print();
    // l1.empty();
    // l1.size();
    // l1.push_back(acc1);
    // l1.empty();
    // l1.size();
    // l1.push_back(acc2);
    // l1.empty();
    // l1.size();
    // l1.push_back(acc1);
    // l1.empty();
    // l1.size();
    // l1.push_back(acc2);
    // l1.empty();
    // l1.size();
    // l1.front();
    // l1.back();
    // l1.print();
    // info_list l2;
    // l2.push_back(acc1);
    // l2.print();
    // l1.pop_front();
    // l1.print();
    // l1.pop_back();
    // l1.print();
    // l1.insert(3, acc2);
    // l1.print();
    // l1.size();
    delete[] str;
    return 0;
}