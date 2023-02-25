// 1. Дополнить текст программы таким образом,
// чтобы все операторы функции main() работали корректно.
// Функцию main не менять, возможна только дополнительная печать.
// Тела перегруженных операторов не должны быть пустыми, должны содержать произвольные, но осмысленные действия.
#include <iostream>
using namespace std;
class Arr
{
    int *arr;
    int size;

public:
    Arr(int s, int date = 0) : size(s)
    {
        arr = new int[s];
        for (int i = 0; i < size; arr[i++] = date)
            ;
    }
    Arr(const Arr &a, int mult = 1)
    {
        size = a.size;
        arr = new int[size];
        for (int i = 0; i < size; i++)
        {
            arr[i] = a.arr[i] * mult;
        };
    }
    ~Arr() { delete[] arr; }

    friend ostream &operator<<(ostream &os, const Arr &dt)
    {
        for (int i = 0; i < dt.size; i++)
            os << dt.arr[i];
        return os;
    };

    friend Arr operator|(const Arr a, const int b)
    {
        Arr tmp(a);
        for (int i = 0; i < a.size; i++)
            tmp.arr[i] += b;
        return tmp;
    };

    Arr &operator=(Arr right)
    {
        size = right.size;
        delete[] arr;
        arr = new int[size];
        for (int i = 0; i < right.size; i++)
            arr[i] = right.arr[i];
        return *this;
    }

    friend Arr operator-(const Arr &a)
    {
        return Arr(a, -1);
    }

    int &operator[](int i)
    {
        return arr[i];
    }

    friend Arr operator|(const Arr &obj1, const Arr &obj2)
    {
        Arr tmp(max(obj1.size, obj2.size));
        for (int i = 0; i < obj1.size; i++)
            tmp.arr[i] += obj1.arr[i];
        for (int i = 0; i < obj2.size; i++)
            tmp.arr[i] += obj2.arr[i];
        return tmp;
    }

    Arr &operator|=(int x)
    {
        for (int i = 0; i < size; i++)
        {
            arr[i] += x;
        }
        return *this;
    }
};

int main()
{
    Arr a1(15), a2(20, 5), a3(30, 3);
    const Arr a4(5);
    cout << a1 << a2 << a3 << a4 << endl;
    a2 = a2 | 2; // объект a2 здесь не меняется
    a2 |= 1;     // а здесь меняется
    a3 = (-a2) | (-a4);
    a3[5] = 10;
    a1 = a4 | a3;
    cout << a1 << a2 << a3 << a4 << endl;
    return 0;
}