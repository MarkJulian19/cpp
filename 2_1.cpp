/*
ДЗ-2.  Срок сдачи — до 11.03.23
1. АТД. Очередь для хранения данных.
На основе класса Списокэлементовпроизвольного_типа ( использовать класс из ДЗ-1) определить класс Очередь, который должен быть производным от Списка.
Элемент данных, помещаемых в очередь  - тот же класс, что использовали в списке.
Максимальный допустимый размер очереди определен по умолчанию, а также может явно указываться при создании  объекта-Очереди.
Определить необходимые конструкторы.
Обеспечить корректное уничтожение объектов.
В классе должны быть функции:
добавления элемента в конец очереди (back),+
чтение первого элемента из очереди без его удаления (front) ,+
удаление первого элемента очереди (pop),+
проверка очереди на пустоту (empty),+
текущее число элементов (size),+
проверка, что очередь целиком заполнена (full).+
вывод информации об элементах очереди без ее изменения (print).+
Функции класса Список должны остаться прежними, а не переделываться под потребности очереди.
Через объект Очередь должны быть доступны только функции, указанные в задании. При этом базовый класс  остается полноценным списком, т.е. в программе могут использоваться и объекты базового класса  Список.
Глобальных переменных быть НЕ должно.
Использование STL и типа string  запрещено.
Функция main должна демонстрировать работу с объектами написанных классов.
Пример работы:  Date d1(…);  Queue  q1(5), q2;  List l1;  q1.back(d1);  l1.push_back(d1);   l1.print(); cout<<q2.size();   и т.д.
*/
#include <iostream>
#include <cstring>
#include "1_1_1.h"

using namespace std;

template <class Type>
class my_queue : info_list<Type>
{
    unsigned int max_size;

public:
    //--------------------------------------------------------------------------------
    // конструкторы, деструкторы
    my_queue(unsigned int i = 10)
    {
        max_size = i;
    };
    //--------------------------------------------------------------------------------
    void back(Type b)
    {
        cout << info_list<Type>::size() << endl;
        cout << max_size << endl;
        if ((info_list<Type>::size()) < max_size )
        {
            info_list<Type>::push_back(b);
        }
        else
        {
            cout << "my_queue is full" << endl;
        }
    };
    void print()
    {
        info_list<Type>::print();
    };
    void front()
    {
        info_list<Type>::front();
    };
    void pop()
    {
        info_list<Type>::pop_front();
    };
    void empty()
    {
        info_list<Type>::empty();
    };
    void size()
    {
        info_list<Type>::size();
    }
    void full()
    {
        if (max_size == this->size())
        {
            cout << "my_queue is full" << endl;
        }
        else
        {
            cout << "my_queue is not full, current number of elements: " << this->list_size << endl;
        }
    }
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
    my_queue<bank_account> a1;
    a1.back(acc1);
    a1.back(acc2);
    a1.back(acc3);
    a1.back(acc4);
    a1.print();
    a1.pop();
    a1.print();
    return 0;
}