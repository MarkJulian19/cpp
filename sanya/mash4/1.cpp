#include <iostream>
using namespace std;

class A{
    int a;
    A(int i=0): a(i){}
    public:
    A(A& tmp){
        a=tmp.a;
    }
    void print(){
        cout<<a;
    }
    static A obj(int x);
};

A A::obj(int x){
    return A(x);
}

int main(){
    int x=10;
    A a=A::obj(x);
    a.print();
    return 0;
}