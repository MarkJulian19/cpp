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
        cout << str << "\n";
    }
};
Str::Str()
{
    str = NULL;
    len = 0;
    cout << "done\n";
}
Str::Str(const char *istr)
{
    str = new char[strlen(istr)];
    strcpy(str, istr);
    len = strlen(istr);
    cout << "done1\n"
         << str << endl;
}
Str::Str(const Str &tmp)
{
    len = tmp.len;
    str = new char[len];
    strcpy(str, tmp.str);
    cout << "done2\n"
         << str << endl;
}
Str::~Str()
{
    delete[] str;
    cout << "done3\n";
}
class Man
{
    Str name;
    int age;

public:
    Man();
    Man(const char *, int);
    Man(const Man &);
    Man(const Str, int);
    Man(Man&&);
    ~Man();
};
Man::Man() : name()
{
    age = 0;
    cout << "man0\n";
}
Man::Man(const char *tmp, int y) : name(tmp)
{
    age = y;
    cout << "man1\n";
}
Man::Man(const Man &tmp) : name(tmp.name)
{
    age = tmp.age;
    cout << "man2\n";
}
Man::Man(const Str tmp, int y) : name(tmp)
{
    age = y;
    cout << "man3\n";
}
Man::~Man()
{
    cout << "manDEL\n";
}
int main()
{
    const char *tmp = "Hello\0";
    Str s1;
    Str s2(tmp);
    Str s3(s2);
    Man m1;
    Man m2(tmp, 5);
    Man m3(m2);
    return 0;
}