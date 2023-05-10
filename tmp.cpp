#include <iostream>

namespace A
{
    int a = 1;
};
namespace B
{
    int a = 2;
};
using namespace std;
int main()
{
    int a = 0;
    using namespace B;
    cout << a;
    return 0;

}