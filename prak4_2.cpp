#include <iostream>
#include <cstring>

using namespace std;

class A
{
    int a;
    static A *p;
    A(int i) : a(i) {}
    A(A &x)
    {
        a = x.a;
    }
    static int counter;
    static A * c;
public:
    static A* create(int i)
    {
        if (counter == 0){
        counter++;
        c = new A(i);
        return c;
        }
        else
            return c;
    }
    void print()
    {
        cout << a << endl;
    }
};
int A::counter=0;
A* A::c = NULL;
int main()
{
    A *k = A::create(1);
    A *g = A::create(5);
    k->print();
    g->print();
}
