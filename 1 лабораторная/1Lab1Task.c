#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long expo(long long a, long long x, long long p);

int main() {
    srand(time(NULL));
    long long a = 2 + rand() % 1000000000;
    long long x = 2 + rand() % 1000000000;
    long long p = 2 + rand() % 1000000000;
    printf("a = %lld\nx = %lld\np = %lld\n", a, x, p);
    printf("Result: %ld\n", expo(a, x, p));
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
