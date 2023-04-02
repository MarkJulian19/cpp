// ДЗ-4. Шаблоны. Срок сдачи — до 01.04.23

// Написать класс-функцию (с перегруженным operator()), для выполнения некоторых действий над передаваемым ей контейнером.
// Действия можете придумать любые (например: поменять местами элементы, реверсировать и т. п.), напишите комментарий, что делаете.

// Функция должна быть применима к list, vector, string, хорошо, если и к массивам встроенных типов.

// Количество параметров в функции - по необходимости.
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <iterator>
using namespace std;
class Exchange {  //Меняет местами элемент p1 и p2
public:
	template <typename CustomType> //Для контейнера
	void operator () (CustomType &obj, int p1, int p2) {
		typename CustomType::iterator i = obj.begin(), j = obj.begin(), tmp;
        for (int k=0; k<p1; k++){
            i++;
        }
        for (int k=0; k<p2; k++){
            j++;
        }
        swap(*i,*j);
	}
	template <typename CustomType> //Для массива
	void operator () (CustomType *arr, int p1, int p2) {
		swap(arr[p1],arr[p2]);
	}
};
template <typename CustomType>
void print(const CustomType & obj) {
	typename CustomType::const_iterator i;
	for (i = obj.begin(); i != obj.end(); i++)
		cout << *i << ' ';
	cout<<endl;
}
int main(){
    Exchange f;
    list<int> L;
    L={1,2,3,4,5};
    print(L);
    f(L, 0, 2);
    print(L);
    vector<int> v1={1,2,3,4,5};
    print(v1);
    f(v1, 0, 2);
    print(v1);
    string s1="abcdef";
    print(s1);;
    f(s1, 0, 2);
    print(s1);
    int s2[5]{1,2,3,4,5};
    for (int i=0; i<5; i++){
        cout<<s2[i]<<' ';
    }
    cout<<endl;
    f(s2,0, 2);
    for (int i=0; i<5; i++){
        cout<<s2[i]<<' ';
    }
    cout<<endl;
    f(s1,0, 2);
}