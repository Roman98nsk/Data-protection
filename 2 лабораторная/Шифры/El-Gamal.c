//сделать общий фацл с вызовом каждого шифра
//сделать функцию кодировки/декодировки для шифра гамаля
//какие сообщения обрабатывать (буквы, цифры, текст...)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

bool isPrime(long long int n);
long long int expo(long long int a, long long int x, long long int p);

int main() {
    long long int p = 0, m = 0, g = 0, c_a = 0, c_b = 0, d_a = 0, d_b = 0, k = 0, r = 0, e = 0, m_new = 0;
    srand(time(NULL));

    do {
        p = 3 + rand() % 100;
    } while (isPrime(p) == 0);

    m = 2 + rand() % (p - 1);

    g = 2 + rand() % (p - 1);

    c_a = 1 + rand() % (p - 1);
    c_b = 1 + rand() % (p - 1);

    d_a = expo(g, c_a, p); 
    d_b = expo(g, c_b, p);

    k = 1 + rand() % (p - 2);

    r = expo(g, k, p);
    e = expo(expo(m, 1, p) * expo(d_b, k, p), 1, p);

    m_new = expo(expo(e, 1, p) * expo(r, p - 1 - c_b, p), 1, p);

    printf("p = %lld, g = %lld, e = %lld, \n", p, g, e);
    printf("m = %lld, m_new = %lld\n", m, m_new);
    return 0;
}

bool isPrime(long long int n) {
    if (n > 1) {
        for (int i = 2; i < n; i++)
            if (n % i == 0)
                return false;
        return true;
    } else
        return false;
}

long long int expo(long long int a, long long int x, long long int p) {
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