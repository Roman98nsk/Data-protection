/*Функция, которая решает задачу нахождения дискретного логарифма 
при помощи алгоритма «Шаг младенца, шаг великана». Трудоёмкость 
работы функции должна соответствовать описанной в учебники и 
составлять . */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

long expo(long long a, long long x, long long p);

int main() {
    int a, x, p, y, m, k, i, j;

    a = 1 + rand() % 10;

    do {
        srand(time(NULL));
        p = 1 + rand() % 10;
        y = 1 + rand() % 10;
    } while(p <= y);

    do {
        m = 1 + rand() % 10;
        k = 1 + rand() % 10;
    } while(m * k <= p);

    int array[m - 1];

    for (int j = 0; j < m - 1; j++) {
        array[j] = (y * a ^ j) % p;
    }

//шаг великана
    int array1[k];

    for (int i = 1; i <= k; i++) {
        array1[i - 1] = a ^ (i * m) % p;
    }

    //найти одинаовое число в массивах

    //индексы элемента поставить в  x = i * m - j. Ищем х, выводим. 
    return 0;
}

long expo(long long a, long long x, long long p) {
    int r;
    long y = 1;
    
    while(x > 0) {
        r = x % 2;

        if (r == 1) {
            y = (y * a) % p;
        }

        a = (a * a) % p;
        x = x / 2;
    }
	return y;
}