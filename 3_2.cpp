/*Написать абстрактный класс (содержание произвольное) и несколько (>=2) производных от него классов.
Определить независимый от этой иерархии класс, который работает с массивом объектов типа абстрактного класса.
Использование STL запрещено.
Функция main должна демонстрировать работу с объектами указанных классов, использование виртуальных функций.
*/
#include <iostream>
#include <typeinfo>
using namespace std;
class Figure
{
public:
    virtual double getV() const = 0;
    virtual double getS() const = 0;
};
class Circle : public Figure
{
    double r;

public:
    Circle(double rad) : r(rad) {}
    double getV() const override
    {
        return 3.14 * r * r;
    }
    double getS() const override
    {
        return 2 * 3.14 * r;
    }
};
class Rectangle : public Figure
{
    double length, width;

public:
    Rectangle(double l, double w) : length(l), width(w) {}
    virtual double getV() const override
    {
        return length * width;
    }
    virtual double getS() const override
    {
        return (length + width) * 2;
    }
};
class Worker
{
    Figure **mas;
    int len;

public:
    Worker(Figure **m, int l) : mas(m), len(l){};
    void print_mas()
    {
        for (int i = 0; i < len; i++)
        {
            cout << "Это объект класса " << typeid(*mas[i]).name() << "\tПлощадь и объем"
                 << "\t" << mas[i]->getV() << "," << mas[i]->getS() << endl;
        }
    }
};
int main()
{
    Circle c1(5);
    Circle c2(4);
    Circle c3(8);
    Rectangle r1(3, 4);
    Rectangle r2(5, 8);
    Rectangle r3(5, 3);
    Figure *mas[6];
    mas[0] = &c1;
    mas[1] = &c2;
    mas[2] = &c3;
    mas[3] = &r1;
    mas[4] = &r2;
    mas[5] = &r3;
    Worker w(mas, 6);
    w.print_mas();
    // cout<<mas[5]->getS()<<endl;
    // cout<<mas[0]->getS()<<endl;
}