#include <iostream>
#include <string>
using namespace std;

class ex2
{
    static unsigned int counter;
    int x;

public:
    ex2()
    {
        counter++;
        // cout << counter << endl;
        cout << "ex2()" << endl;
    }
    ~ex2()
    {
        counter--;
        // cout << counter << endl;
        cout << "~ex2()" << endl;
    }
    void get_counter(){
        cout << counter << endl;
    } 
};

unsigned int ex2::counter = 0;

int main()
{
    ex2 a;
    a.get_counter();
    ex2 b;
    b.get_counter();
    ex2 c;
    c.get_counter();
    return 0;
}