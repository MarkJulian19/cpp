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

int main(){
    char c = 254;
    BINPRINT(c);
    c=c^4;
    printf("%c",c);
    BINPRINT(c);
    c=c~4;
    BINPRINT(c);
    return 0;
}