#include <iostream>
#include <ctime>
#include <time.h>
int main()
{
    unsigned int start_time = clock();
    int a, b = 0;
    for (a = 1000000000; a > 0; a = a - 1)
    {
        b = b + 1;
    }
    unsigned int end_time = clock();
    std::cout << 1000.0 * (end_time - start_time) / CLOCKS_PER_SEC << std::endl;
    return 0;
}