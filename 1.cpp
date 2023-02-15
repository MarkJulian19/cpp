#include <iostream>
#include <string>
using namespace std;

class me
{
public:
    int age;
    string name;
    void outinf()
    {
        cout << age << endl;
        cout << name << endl;
        cout << color << endl;
    }
    int Getcolor()
    {
        return color;
    }
    void Setcolor()
    {
        color = 11;
    }

private:
    int color = 10;
};

int main()
{
    me h1;
    h1.age = 19;
    cin >> h1.name;
    system("clear");
    // cout << h1.age << endl;
    // cout << h1.name << endl;
    h1.outinf();
    return 0;
}
