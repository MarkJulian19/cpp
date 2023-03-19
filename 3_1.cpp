/*Написать абстрактный класс (содержание произвольное) и несколько (>=2) производных от него классов.
Определить независимый от этой иерархии класс, который работает с массивом объектов типа абстрактного класса.
Использование STL запрещено.
Функция main должна демонстрировать работу с объектами указанных классов, использование виртуальных функций.
*/
#include <iostream>
#include <typeinfo>
using namespace std;

class Shape
{
public:
    virtual double getPerimeter() = 0;
    virtual double getSquare() = 0;
    virtual double getVolume() = 0;
    virtual void getInf() = 0;
    virtual ~Shape() {}
};

class Parallelepiped : public Shape
{
    double x;
    double y;
    double z;

public:
    Parallelepiped(double length = 0, double hight = 0, double width = 0)
    {
        x = length;
        y = hight;
        z = width;
    };
    double getPerimeter() override
    {
        return 4 * (x + y + z);
    };
    double getSquare() override
    {
        return 2 * (x * y + x * z + y * z);
    };
    double getVolume() override
    {
        return x * y * z;
    };
    void getInf()
    {
        cout << "length=" << x << ", hight=" << y << ", width=" << z;
    }
    ~Parallelepiped() {}
};

class Ball : public Shape
{
    double rad;

public:
    Ball(double r = 0) : rad(r){};
    double getPerimeter() override
    {
        return 0;
    };
    double getSquare() override
    {
        return 4 * 3.14159 * rad * rad;
    };
    double getVolume() override
    {
        return 4. / 3 * 3.14159 * rad * rad * rad;
    };
    void getInf()
    {
        cout << "rad=" << rad;
    }
};

class mass_of_shapes
{
    int len_mass;
    Shape **mass;
    typedef Shape *pointer;

public:
    mass_of_shapes()
    {
        len_mass = 0;
        mass = new pointer[10];
    };
    template <class T>
    void push(const T &p)
    {
        mass[len_mass++] = new T(p);
    }
    void print_inf_of_shapes()
    {
        for (int i = 0; i < len_mass; i++)
        {
            cout << "Class name: " << typeid(*mass[i]).name() << "class inf: ";
            mass[i]->getInf();
            cout << " P:" << mass[i]->getPerimeter() << " S:"
                 << mass[i]->getSquare() << " V:" << mass[i]->getVolume() << endl;
        }
    }
    ~mass_of_shapes()
    {
        for (int i = 0; i < len_mass; i++)
            delete mass[i];
        delete[] mass;
    }
};

int main()
{
    Parallelepiped p1(3, 4, 5);
    Parallelepiped p2(1, 4, 6);
    Parallelepiped p3(6, 3, 5);
    Ball b1(1.2);
    Ball b2(13.5);
    Ball b3(6);

    mass_of_shapes mas;
    mas.push(p1);
    mas.push(p2);
    mas.push(p3);
    mas.push(b1);
    mas.push(b2);
    mas.push(b3);
    mas.print_inf_of_shapes();
    return 0;
}
