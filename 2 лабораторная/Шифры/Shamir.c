#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

bool isPrime(long long int n);
long long int expo(long long int a, long long int x, long long int p);
long long int gcd(long long int n1, long long int n2);

int main() {
    long long int p = 0, m = 0, c_a = 0, d_a = 0, c_b = 0, d_b = 0, x1 = 0, x2 = 0, x3 = 0, x4 = 0;
    srand(time(NULL));

    do {
        p = 2 + rand() % 20;
        m = 2 + rand() % 20;
    } while (!isPrime(p) || m >= p);

    do {
        c_a = 2 + rand() % 20; 
        d_a = 2 + rand() % (p - 1);
    } while ((c_a * d_a) % (p - 1) != 1 || gcd(c_a, p - 1) != 1);

    do {
        c_b = 2 + rand() % 20;
        d_b = 2 + rand() % (p - 1);
    } while ((c_b * d_b) % (p - 1) != 1 || gcd(c_b, p - 1) != 1);

    x1 = expo(m, c_a, p);
    x2 = expo(x1, c_b, p);
    x3 = expo(x2, d_a, p);
    x4 = expo(x3, d_b, p);
    
    printf("m = %lld, x4 = %lld\n", m, x4);

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

long long int gcd(long long int n1, long long int n2) {
  long long int div;
  if (n1 == n2)
    return n1;

  long long int d = n1 - n2;
  if (d < 0) {
    d = -d;
    div = gcd(n1, d);
  } else {
    div = gcd(n2, d);
  }
  return div;
}