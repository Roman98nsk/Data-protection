/*Функция построения общего ключа для двух абонентов по схеме 
Диффи-Хеллмана*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

long expo(long long a, long long x, long long p);
bool isPrime(long long int n);

int main() {
    long long int p = 0, g = 8, q = 5, Xa, Xb, Xc, Ya, Yb, Yc, Zab, Zba, Zac, Zca, Zbc, Zcb;

    do {
        srand(time(NULL));
        q = 2 + rand() % 10; 
        p = 2 * q + 1;
    } while(!isPrime(p) || !isPrime(q));

    do {
        g = rand() % (p - 1);
    } while (!((expo(g, q, p)) != 1) || !(g > 1));

    printf("p = %lld, q = %lld, g = %lld\n", p, q, g);

    Xa = 1 + rand() % 100;
    Xb = 1 + rand() % 100;
    Xc = 1 + rand() % 100;
    printf("Secret key: Xa = %lld, Xb = %lld, Xc = %lld\n", Xa, Xb, Xc);

    Ya = expo(g, Xa, p);
    Yb = expo(g, Xb, p);
    Yc = expo(g, Xc, p);
    printf("Open key: Ya = %lld, Yb = %lld, Yc = %lld\n", Ya, Yb, Yc);

    Zab = expo(Yb, Xa, p);
    Zba = expo(Ya, Xb, p);
    Zac = expo(Yc, Xa, p);
    Zca = expo(Ya, Xc, p);
    Zbc = expo(Yc, Xb, p);
    Zcb = expo(Yb, Xc, p);
    printf("Zab = %lld, Zba = %lld, Zac = %lld, Zca = %lld, Zbc = %lld, Zcb = %lld\n", Zab, Zba, Zac, Zca, Zbc, Zcb);
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

bool isPrime(long long int n) {
    if (n > 1) {
        for (int i = 2; i < n; i++)
            if (n % i == 0)
                return false;
        return true;
    } else
        return false;
}
