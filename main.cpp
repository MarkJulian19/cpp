#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class Str
{
    char *str;
    int len;

public:
    Str();
    Str(const char *);
    Str(const Str &);
    ~Str();
    void Getstr()
    {
        cout << str;
    }
};

Str::Str()
{
    str = NULL;
    len = 0;
    cout << "Str()" << endl;
};

Str::Str(const char *a)
{
    len = strlen(a);
    str = new char[len];
    strcpy(str, a);
    cout << "Str(const char *a)" << endl;
    cout << str << endl;
};

Str::Str(const Str &a)
{
    len = a.len;
    str = new char[len];
    strcpy(str, a.str);
    cout << "Str(const Str &a)" << endl;
    cout << str << endl;
};

Str::~Str()
{
    if (str != NULL)
    {
        delete[] str;
    }
    cout << "~Str()" << endl;
};

class Man
{
    Str name;
    int age;

public:
    Man();
    Man(const char *, int);
    Man(const Man &);
    ~Man();
};

Man::Man()
{
    age = 0;
    cout << "Man()" << endl;
};

Man::Man(const char *a, int b) : name(a)
{
    age = b;
    cout << "Man(const char *a, int b)" << endl;
    name.Getstr();
    cout << age << endl;
};

Man::Man(const Man &a) : name(a.name)
{
    age = a.age;
    cout << "Man(const Man &a))" << endl;
    name.Getstr();
    cout << age << endl;
};

Man::~Man()
{
    // name.~Str();
    cout << "Man()" << endl;
};

int main()
{
    const char *tmp_char = "Hallo\0";
    Str tmp;
    Str tmp1(tmp_char);
    Str tmp2(tmp1);

    Man mtmp;
    Man mtmp2(tmp_char, 15);
    Man mtmp3(mtmp2);

    return 0;
}
