#include <stdio.h>
int main(){
    long long s = 0;
    int c;
    while(((c = getchar()) != EOF)){
        if ((c >= '0') && (c <= '9')) s += c - '0';
        if ((c >= 'a') && (c <= 'f')) s += c + 10 - 'a';
        if ((c >= 'A') && (c <= 'F')) s += c + 10 - 'A';
    }
    printf("%lld\n",s);
    return 0;
}