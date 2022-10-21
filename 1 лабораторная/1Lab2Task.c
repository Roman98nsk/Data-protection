/*Функция, реализующая обобщённый алгоритм Евклида. Функция 
должна позволять находить наибольший общий делитель и обе 
неизвестных из уравнения.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    //long long a = 2 + rand() % 100000000;
    //long long b = 2 + rand() % 100000000;

    long long a = 101;
    long long b = 192;

    printf("%lld %lld\n", a, b);

    if (b > a) {
        long long tmp = a;
        a = b;
        b = tmp;
        printf("Swap complete\n%lld %lld\n", a, b);
    }

    int U[3] = {a, 1, 0};
    int V[3] = {b, 0, 1};

    if (a > 0 && b > 0 && a >= b) {
        while (V[0] != 0) {
            int q = U[0] / V[0];
            int T[3] = {U[0] % V[0], U[1] - q * V[1], U[2] - q * V[2]};
            U[0] = V[0];
            U[1] = V[1];
            U[2] = V[2];
            V[0] = T[0];
            V[1] = T[1];
            V[2] = T[2];
        }
        printf("x = %d\ny = %d\n", U[1], U[2]);
        printf("%d\n", *U);
        printf("%d", a * U[1] + b * U[2] == U[0]);
    } else {
        printf("n/a\n");
        return 0;
    }
    return 0;
}