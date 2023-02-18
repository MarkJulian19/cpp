#include <iostream>

using namespace std;

class complex_num
{
    int re, im;

public:
    complex_num(const int a, const int b)
    {
        this->re = a;
        this->im = b;
    }
    void add(complex_num a)
    {
        this->re += a.re;
        this->im += a.im;
    }
    void sub(complex_num & a)
    {
        this->re -= a.re;
        this->im -= a.im;
    }
    bool compare(complex_num a)
    {
        if (a.re == this->re && a.im == this->im)
            return true;
        return false;
    }
    void multiply(complex_num a)
    {
        this->re = this->re * a.re - this->im * a.im;
        this->im = this->im * a.re + this->re * a.im;
    }
    int get_re()
    {
        return this->re;
    }
    int get_im()
    {
        return this->im;
    }
};

int main()
{
    complex_num com1(1, 2), com2(3, 4), com3(5, 6), com4(-1, 0);
    cout << com1.get_re() << " i" << com1.get_im() << endl;
    cout << com2.get_re() << " i" << com2.get_im() << endl;
    cout << com3.get_re() << " i" << com3.get_im() << endl;
    cout << com4.get_re() << " i" << com4.get_im() << endl << endl;

    com1.add(com2);
    cout << com1.get_re() << " i" << com1.get_im() << endl << endl;

    com1.sub(com3);
    cout << com1.get_re() << " i" << com1.get_im() << endl << endl;

    cout << com1.get_re() << " i" << com1.get_im() << endl;
    cout << com4.get_re() << " i" << com4.get_im() << endl;
    cout << com1.compare(com4) << endl<< endl;
    
    com2.multiply(com3);
    cout << com2.get_re() << " i" << com2.get_im() << endl;
}
