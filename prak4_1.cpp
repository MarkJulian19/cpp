#include <iostream>
#include <cstring>

using namespace std;

class A
{
    int a;
    A(int i) : a(i) {}
    A(A &x)
    {
        a = x.a;
    }
    // static int counter;
public:
    static A create(int i)
    {
        return A(i);
    }
    void print()
    {
        cout << a << endl;
    }
};
// int A::counter=0;
int main()
{
    A k = A::create(1);
    k.print();
}
