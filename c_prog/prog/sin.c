#include <stdio.h>
float stepen(float base, float exponent)
{
    if (exponent > 0)
        return base * stepen(base, exponent - 1);
    else
        return 1;
}

long long factorial(int N)
{
    if (N == 0)
        return 1;
    return N * factorial(N - 1);
}

float sin_x(float x, float E)
{
    float h, z = 0.0f;
    int n = 0;
    while (1)
    {
        h = (stepen(-1.0f, n) * stepen(x, 2 * n + 1)) / factorial(2 * n + 1);
        
        printf("%.15f\n", h);
        printf("%.15f\n", z);
        z+=h;
        if (h < 0) h = h*(-1.0f);
        if (h < E) break;
        n++;
    }
    return z;
}
int main(){
    float x,E;
    printf("Введите аргумент: ");
    scanf("%f", &x);
    printf("Введите погрешность: ");
    scanf("%f", &E);
    printf("%.15f\n", sin_x(x, E));
    return 0;
}