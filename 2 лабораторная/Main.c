#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <malloc.h>

int El_Gamal(long long int m);
int RSA(long long int m);
int Shamir(long long int m);
int Vernam(long long int m);

bool isPrime(long long int n);
long long int expo(long long int a, long long int x, long long int p);
long long int gcd(long long int n1, long long int n2);
long long int Euclid(long long int a, long long int b);

int main() {
    int find;
    long long int m = 0;

    FILE *file;
    int i;
    //тут хранится путь
    char filename[BUFSIZ];
    //сюда считаем файл
    char write_file[BUFSIZ];

    printf("Введите путь до файла: ");
    scanf("%s", filename);
    file = fopen(filename, "rb");

    while ((write_file[i] = fgetc(file)) != EOF) {
        m++;
        if (write_file[i] == '\n') {
            write_file[i] = '\0';
            //printf("%s\n", write_file);
            i = 0;
        } else i++;
    }
    write_file[i] = '\0';

    printf("Выберите шифр (Gamal - '1', RSA - '2', Shamir - '3', Vernam - '4'):\n");
    scanf("%d", &find);

    switch (find) {
        case 1: {
            El_Gamal(m);
            break;
        }

        case 2: {
            RSA(m);
            break;
        }
        
        case 3: {
            Shamir(m);
            break;
        }

        case 4: {
            Vernam(m);
            break;
        }
    }
    fclose(file);
    return 0;
}

int El_Gamal(long long int m) {
    long long int p = 0, g = 0, c_a = 0, c_b = 0, d_a = 0, d_b = 0, k = 0, r = 0, e = 0, m_new = 0;
    srand(time(NULL));

    do {
        p = 3 + rand() % 1000000;
    } while (isPrime(p) == 0);

    //m = 2 + rand() % (p - 1);

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

int RSA(long long int m) {
    long long int P_A = 0, P_B = 0, Q_A = 0, Q_B = 0, N_A = 0, N_B = 0, f_A = 0, f_B = 0, d_A = 0, d_B = 0, c_A = 0, c_B = 0, m_new = 0, e = 0;
    srand(time(NULL));

    do {
        P_A = rand() % 1000000;
        Q_A = rand() % 1000000;
    } while (!isPrime(P_A) || !isPrime(Q_A));

    N_A = P_A * Q_A;
    
    f_A = (P_A - 1) * (Q_A - 1);

    do {
        d_A = 2 + rand() % (f_A - 2);
    } while (gcd(d_A, f_A) != 1);

    printf("d_a = %lld, f_A = %lld\n", d_A, f_A);

    c_A = Euclid(d_A, f_A);

    if ((c_A * f_A) % d_A != 1 && (c_A * d_A) % f_A != 1) {
        printf("Euclid error\n");
        //return 0;
    }
    //-2 % 10 = -2 (+10)
    do {
        P_B = rand() % 1000000;
        Q_B = rand() % 1000000;
    } while (!isPrime(P_B) || !isPrime(Q_B));

    N_B = P_B * Q_B;
    
    f_B = (P_B - 1) * (Q_B - 1);

    do {
        d_B = 2 + rand() % (f_B - 2);
    } while (gcd(d_B, f_B) != 1);

    c_B = Euclid(d_B, f_B);

    if((c_B * f_B) % d_B != 1 && (c_B * d_B) % f_B != 1) {
        printf("Euclid error\n");
       // return 0;
    }

    //m = rand() % N_B;

    e = expo(m, d_B, N_B);

    m_new = expo(e, c_B, N_B);

    printf("m = %lld, m_new = %lld\n", m, m_new);
    return 0;
}

int Shamir(long long int m) {
    long long int p = 0, c_a = 0, d_a = 0, c_b = 0, d_b = 0, x1 = 0, x2 = 0, x3 = 0, x4 = 0;
    srand(time(NULL));

    do {
        p = 2 + rand() % 1000000;
        //m = 2 + rand() % 20;
    } while (!isPrime(p) || m >= p);

    do {
        c_a = 2 + rand() % 100000; 
        d_a = 2 + rand() % (p - 1);
    } while ((c_a * d_a) % (p - 1) != 1 || gcd(c_a, p - 1) != 1);

    do {
        c_b = 2 + rand() % 100000;
        d_b = 2 + rand() % (p - 1);
    } while ((c_b * d_b) % (p - 1) != 1 || gcd(c_b, p - 1) != 1);

    x1 = expo(m, c_a, p);
    x2 = expo(x1, c_b, p);
    x3 = expo(x2, d_a, p);
    x4 = expo(x3, d_b, p);
    
    printf("m = %lld, x4 = %lld\n", m, x4);

    return 0;
}

int Vernam(long long int m) {
    long long int k = 0, e = 0, c = 1, count = 0, m_new = 0;
    srand(time(NULL));

    while(1) {
        if(m < c) {
            break;
        }
        count++;
        c *= 2;
    }

    k = c / 2 + rand() % c / 2;

    e = m ^ k;
    printf("m = %lld, k = %lld, e = %lld, \n", m, k, e);
    m_new = e ^ k;
    printf("m decode = %lld\n", m_new);
    return e;
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
    printf("x = %d\n", U[1]);
    return U[1];
}