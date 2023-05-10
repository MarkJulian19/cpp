#include <stdio.h>
#include <limits.h>
#define BINPRINT(num)                                      \
    {                                                      \
        unsigned long long _x, _t;                         \
        unsigned long long _length = 64 - sizeof(num) * 8; \
        _x = num;                                          \
        for (int _i = 1; _i <= 64; _i++)                   \
        {                                                  \
            if (_i > _length)                              \
            {                                              \
                _t = _x;                                   \
                if ((_t & 0x8000000000000000) == 0)        \
                    printf("0");                           \
                else                                       \
                    printf("1");                           \
            }                                              \
            _x = _x << 1;                                  \
        }                                                  \
        printf("\n");                                      \
    }

int main()
{
    printf("Hello!\nBinar converter programm is running...\n");
    int i = 1;
    while (i != 0)
    {
        printf("Enter char value:\n");
        int c;
        scanf("%d", &c);
        if (c != 0)
        {
            BINPRINT((char)c);
        }
        int sh;
        printf("Enter short value:\n");
        scanf("%d", &sh);
        if (sh != 0)
        {
            BINPRINT((short)sh);
        }
        printf("Enter int value:\n");
        int x;
        scanf("%d", &x);
        if (x != 0)
        {
            BINPRINT(x);
        }
        long long l;
        printf("Enter long long value:\n");
        scanf("%lld", &l);
        if (l != 0)
        {
            BINPRINT(l);
        }
        BINPRINT((long long)x);
        BINPRINT((long long)LLONG_MAX);
        BINPRINT((long long)ULLONG_MAX);
        printf("If you want to enter new values print 1, if not, print 0:\n");
        scanf("%d", &i);
    }
    return 0;
}