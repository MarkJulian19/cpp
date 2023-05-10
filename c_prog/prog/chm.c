// заданные значения функции
// f(0..30)=0
// f(31..60)=0.1
// f(61..N)=0
#include <stdio.h>
#include <stdlib.h>
#define N 1000     // количесво уравнений в системе по заданию 100 или 1000
#define gamma 1.5 // коэфф гамма данный по заданию

void result_print(long double *y, long double *f)
{ // выпишем все решения в консоль и файл для удобства дальнейшего использования(консоль не всегда все значения может вместить)
    FILE *file = fopen("out.txt", "w");
    printf("System: \n");
    printf("-%.1f * y_(i - 1) + 2 * y_i + %.1f * y_(i + 1) = f_i , i = 1, ... , N - 1; \n", gamma, gamma);
    printf("y_0 = f_0; \n");
    printf("y_n = f_n; \n");
    printf("Vector f: \n");
    for (int i = 0; i < N + 1; i++)
    {
        fprintf(file, "%.1Lf\n", f[i]);
        printf("%d. %.1Lf\n", i, f[i]);
    }
    printf("\nVector y:\n");
    for (int i = 0; i < N + 1; i++)
    {
        fprintf(file, "%Le\n", y[i]);
        printf("%d. %Le\n", i, y[i]);
    }
    fclose(file);
    printf("\nThe program was finished successfully\n");
}
int main()
{
    long double *f = (long double *)malloc((N + 2) * sizeof(long double)); // вектор f память под правую часть системы

    for (int i = 0; i <= 30; i++) // задаем вектор f
    {
        f[i] = 0;
    }
    for (int i = 31; i <= 60; i++)
    {
        f[i] = 0.1;
    }
    for (int i = 61; i <= N; i++)
    {
        f[i] = 0;
    } // формируем вектор f

    long double *a = (long double *)malloc((N) * sizeof(long double)); // нижняя диаг
    long double *b = (long double *)malloc((N) * sizeof(long double)); // верхняя диаг
    long double *c = (long double *)malloc((N) * sizeof(long double)); // средняя диаг

    // a=-gamma b=2 c=gamma задаем вектора коэфф трехдиаг матрицы
    a[0] = 0; // не исп
    b[0] = 0;
    c[0] = 0;
    for (int i = 1; i < N; i++)
    {
        a[i] = 0 - gamma;
        c[i] = 2;
        b[i] = gamma;
    } // формируем векторы диагоналей

    long double *y = (long double *)malloc((N + 2) * sizeof(long double)); // вектор решений
    // неизвестные решения системы будут находиться по формуле: y_(i - 1) = alpha_(i - 1) * y_i + betta_(i - 1)
    long double *alpha = (long double *)malloc((N + 2) * sizeof(long double));
    long double *betta = (long double *)malloc((N + 2) * sizeof(long double));

    alpha[0] = 0;
    betta[0] = 0;
    alpha[1] = 0;
    betta[1] = f[0];

    for (int i = 1; i < N; i++) // найдем все альфа и бета в наших иттерациях
    {
        alpha[i + 1] = 0 - b[i] / (a[i] * alpha[i] + c[i]);
        betta[i + 1] = (f[i] - a[i] * betta[i]) / (a[i] * alpha[i] + c[i]);
    } // формируем вектор альфа и вектор бета для нахождения решений

    y[0] = f[0]; // изначальное условие задачи
    y[N] = f[N]; // изначальное условие задачи
    for (int i = N - 1; i > 0; i--)
    {
        y[i] = alpha[i + 1] * y[i + 1] + betta[i + 1];
    }                   // находим решения методом прогонки
    result_print(y, f); // выводим решения в консоль и в файл
    free(f);
    free(a);
    free(b);
    free(c);
    free(y);
    free(alpha);
    free(betta); // освобождаем память
    return 0;
}