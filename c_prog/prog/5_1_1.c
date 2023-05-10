#include <stdio.h>
#include <limits.h>

#define BINPRINT(xe){\
    do {\
    unsigned long long _t = 0, _k = 0, _x;\
    unsigned long long _length = sizeof(xe)*8;\
    _x = xe;\
    for (int _i = 0; _i < _length; _i++){\
        _k = _x%2;\
        _x = _x/2;\
        _t = _t*2;\
        _t = _t|_k;\
    }\
    for (int _i = 0; _i < _length; _i++){\
        _x = _t%2;\
        _t = _t/2;\
        printf("%ld", _x);\
    }\
    printf("\n");\
    }while(0);\
}

int main()
{
    printf("Hello!\nBinar converter programm is running...\n");
        int i = 1;
    while (i != 0){
     printf("Enter c value:\n");
    int c;
    scanf("%d", &c);
    if(c != 0) {
        BINPRINT((char) c);
    }else{ printf("Zero!\n");}

    BINPRINT((short)7);
    printf("Enter x value:\n");
    long x;
    scanf("%ld", &x);
    if (x != 0) {BINPRINT(x);
    }else{
        printf("Zero!\n");}
    BINPRINT((long long)x);
    BINPRINT((long long)LLONG_MAX);
    BINPRINT((long long)ULLONG_MAX);
    printf("If you want to enter new values print 1, if not, print 0:\n");

    scanf("%d", &i);
}
    return 0;
}