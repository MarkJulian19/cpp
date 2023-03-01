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
using namespace std;

class Order_Info
{
    char *company_id;
    long long int phone_number, order_id;
    static unsigned int orders_intotal;

public:
    Order_Info()
    {
        company_id = NULL;
        phone_number = 0;
        order_id=orders_intotal;
        orders_intotal++;
    }
    Order_Info(const char *cmpny, long long int pn)
    {
        company_id = new char[strlen(cmpny) + 1];
        strcpy(company_id, cmpny);
        phone_number = pn;
        order_id = orders_intotal + 1;
        orders_intotal++;
    }
    Order_Info(Order_Info &tmp)
    {
        company_id = new char[strlen(tmp.company_id) + 1];
        strcpy(company_id, tmp.company_id);
        order_id = tmp.order_id;
        phone_number = tmp.phone_number;
    }
    ~Order_Info()
    {
        delete[] company_id;
        //cout<<"Deleted"<<order_id<<endl;
    }
    unsigned int get_order_id()
    {
        return order_id;
    }
    unsigned int get_phone_number()
    {
        return phone_number;
    }
    unsigned int get_orders_intotal()
    {
        return orders_intotal;
    }
    Order_Info *operator=(Order_Info &tmp)
    {
        if(this==&tmp) {
            cout<<"SAME\n";
            return this;
        }
        delete []company_id;
        company_id = new char[strlen(tmp.company_id) + 1];
        strcpy(company_id, tmp.company_id);
        order_id = tmp.order_id;
        phone_number = tmp.phone_number;
        return this;
    }
    void get_info()
    {
        cout << "Заказ из " << company_id << endl;
        cout << "Номер заказа: №" << order_id << endl;
        cout << "Номер телефона клиента: " << phone_number << endl;
        return;
    }
};

unsigned int Order_Info::orders_intotal = 0;

template <typename Custom_Type>
class List_Of_Info
{
    struct List
    {
        List *next;
        List *prev;
        Custom_Type info;
    };
    List *top, *bot;
    unsigned int size;

public:
    List_Of_Info()
    {
        top = NULL;
        bot = NULL;
        size = 0;
    };
    ~List_Of_Info()
    {
        List *tmp;
        while (top != NULL)
        {
            tmp = top->next;
            delete top;
            top = tmp;
        }
    };
    void push_top(Custom_Type tmp)
    {
        if (top == NULL)
        {
            top = new List;
            top->next = NULL;
            top->prev = NULL;
            bot = top;
        }
        else
        {
            List *node = new List;
            node->next = top;
            node->prev = NULL;
            top->prev = node;
            top = node;
        }
        top->info = tmp;
        size++;
        return;
    };
    void push_bot(Custom_Type tmp)
    {
        if (bot == NULL)
        {
            bot = new List;
            bot->next = NULL;
            bot->prev = NULL;
            top = bot;
        }
        else
        {
            List *node = new List;
            node->next = NULL;
            node->prev = bot;
            bot->next = node;
            bot = node;
        }
        bot->info = tmp;
        size++;
        return;
    };
    void push_count(Custom_Type tmp, unsigned int count)
    {
        if (size < count)
        {
            cout << "Cant fit counter\n";
            return;
        }
        List *tmp_list = top;
        unsigned int i = 1;
        while (i < count)
        {
            tmp_list = tmp_list->next;
            i++;
        }
        List *imported = new List;
        tmp_list->prev->next = imported;
        imported->prev = tmp_list->prev;
        tmp_list->prev = imported;
        imported->next = tmp_list;
        imported->info = tmp;
        size++;
        return;
    };
    void pop_top()
    {
        if (top == NULL)
        {
            cout << "Cant pop top";
            return;
        }
        List *tmp = top;
        top = top->next;
        top->prev = NULL;
        size--;
        delete tmp;
    };
    void pop_bot()
    {
        if (bot == NULL)
        {
            cout << "Cant pop bot";
            return;
        }
        List *tmp = top;
        bot = bot->prev;
        bot->next = NULL;
        size--;
        delete tmp;
    };
    void pop_count(unsigned int count)
    {
        if (size < count)
        {
            cout << "Cant fit counter\n";
            return;
        }
        List *tmp = top;
        unsigned int i = 1;
        while (i < count)
        {
            tmp = tmp->next;
            i++;
        }
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        size--;
        delete tmp;
        return;
    };
    unsigned int getsize()
    {
        return size;
    };
    void print_top(){
        if(top){
            top->info.get_info();
            return;
        }
        else{
            cout<<"Empty list\n";
            return;
        }
    }
    void print_bot(){
        if(top){
            bot->info.get_info();
            return;
        }
        else{
            cout<<"Empty list\n";
            return;
        }
    }
    void print_list()
    {
        if (size)
        {
            List *tmp = top;
            while (tmp)
            {
                tmp->info.get_info();
                tmp = tmp->next;
            }
        }
        else
        {
            cout << "List is empty" << endl;
        }
    };
};
int main()
{
    const char *cmp1 = "Yandex";
    const char *cmp2 = "Ebay";
    const char *cmp3 = "Amazon";
    const char *cmp4 = "Ozon";
    long long int num1 = 89629532849;
    long long int num2 = 84938275834;
    long long int num3 = 85940302348;
    long long int num4 = 84233459490;
    Order_Info ord1(cmp1, num1);
    Order_Info ord2(cmp2, num2);
    Order_Info ord3(cmp3, num3);
    Order_Info ord4(cmp4, num4);
    List_Of_Info<Order_Info> list_def;
    cout<<"______Добавим сверху элемент. Выведем верхний и нижний\n";
    list_def.push_top(ord1);
    list_def.print_top();
    list_def.print_bot();
    cout<<"______Добавим еще один сверху. Выведем верхний и нижний\n";
    list_def.push_top(ord2);
    list_def.print_top();
    list_def.print_bot();
    cout<<"______Добавим 3 элемент между ними, вывод всего списка\n";
    list_def.push_count(ord3, 2);
    list_def.print_list();
    cout<<"______Добавим сверху 4 элемент. Вывод всего списка\n";
    list_def.push_top(ord4);
    list_def.print_list();
    cout<<"______Выкинем из списка верхний элемент. Вернём его же в конец списка. Вывод всего списка\n";
    list_def.pop_top();
    list_def.push_bot(ord4);
    list_def.print_list();
    cout<<"______Выкинем из списка 2 элемент. Вывод всего списка\n";
    list_def.pop_count(2);
    list_def.print_list();
}
