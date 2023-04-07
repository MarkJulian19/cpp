// Написать класс-функцию (с перегруженным operator()), для выполнения некоторых действий над передаваемым ей контейнером.
// Действия можете придумать любые (например: поменять местами элементы, реверсировать и т. п.), напишите комментарий, что делаете.
// Функция должна быть применима к list, vector, string, хорошо, если и к массивам встроенных типов.
// Количество параметров в функции - по необходимости.
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <iterator>
using namespace std;

class Rev // Переворачивает массив
{
public:
    template <typename Container> 
    void operator()(Container &obj)
    {
        reverse(obj.begin(), obj.end());
    }

    template <typename Container> 
    void operator()(Container *arr, int n)
    {
        for (int i = 0, j = n-1; i < j; i++, j--)
            swap(arr[i], arr[j]);
    }
};

template <typename Container>
void print(const Container &obj)
{
    typename Container::const_iterator i;
    for (i = obj.begin(); i != obj.end(); i++)
        cout << *i << ' ';
    cout << endl;
}

int main()
{
    Rev fun;
    vector<int> V{1, 2, 3, 4, 5};
    cout << "vector" << endl;
    print(V);
    fun(V);
    print(V);

    int M[] = {1, 2, 3, 4, 5};
    cout << "mass" << endl;
    for (int i = 0; i < (sizeof(M) / sizeof(int)); i++)
    {
        cout << M[i] << " ";
    }
    cout << endl;
    fun(M, sizeof(M) / sizeof(int));
    for (int i = 0; i < (sizeof(M) / sizeof(int)); i++)
    {
        cout << M[i] << " ";
    }
    cout << endl;

    cout << "list" << endl;
    list<int> L;
    L={1,2,3,4,5};
    print(L);
    fun(L);
    print(L);

    cout << "string" << endl;
    string s="1245";
    print(s);
    fun(s);
    print(s);
}