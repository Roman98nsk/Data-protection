#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

bool isPrime(long long int n);
long long int gcd(long long int n1, long long int n2);
long long int Euclid(long long int a, long long int b);
long long int expo(long long int a, long long int x, long long int p);

int main() {
    long long int P_A = 0, P_B = 0, Q_A = 0, Q_B = 0, N_A = 0, N_B = 0, f_A = 0, f_B = 0, d_A = 0, d_B = 0, c_A = 0, c_B = 0, m = 0, m_new = 0, e = 0;
    srand(time(NULL));

    do {
        P_A = 2 + rand() % 10;
        Q_A = 2 + rand() % 10;
    } while (!isPrime(P_A) || !isPrime(Q_A));

    N_A = P_A * Q_A;
    
    f_A = (P_A - 1) * (Q_A - 1);

    do {
        d_A = 2 + rand() % (f_A - 2);
        c_A = Euclid(f_A, d_A); 
    } while (gcd(d_A, f_A) != 1 || c_A * f_A % d_A != 1);

    printf("c_A = %lld, d_A = %lld, f_A = %lld\n", c_A, d_A, f_A);

    do {
        P_B = 2 + rand() % 10;
        Q_B = 2 + rand() % 10;
    } while (!isPrime(P_B) || !isPrime(Q_B));

    N_B = P_B * Q_B;

    f_B = (P_B - 1) * (Q_B - 1);

    do {
        d_B = 2 + rand() % (f_B - 2);
        c_B = Euclid(f_B, d_B);
    } while (gcd(d_B, f_B) != 1 || c_B * f_B % d_B != 1);

    m = rand() % N_B;

    e = expo(m, d_B, N_B);

    m_new = expo(e, c_B, N_B);

    printf("N_B = %lld, m = %lld, m_new = %lld\n", N_B, m, m_new);
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

long long int Euclid(long long int a, long long int b) {
    if (b > a) {
        long long tmp = a;
        a = b;
        b = tmp;
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
    } else {
        printf("n/a\n");
        return 0;
    }
    //printf("x = %d\n", U[1]);
    return U[1];
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