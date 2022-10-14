/*Функция, которая решает задачу нахождения дискретного логарифма 
при помощи алгоритма «Шаг младенца, шаг великана». Трудоёмкость 
работы функции должна соответствовать описанной в учебнике и 
составлять . */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

long long expo(long long a, long long x, long long p);

int main() {
    long long a = 0, x = 0, p = 0, y = 0;

    srand(time(NULL));
    p = 2 + rand() % 100;
    long long m = sqrt(p) + 1;
    long long k = m;
    a = 2 + rand() % 100;
    y = 2 + rand() % p;
   
    printf("a = %lld, y = %lld\n", a, y);
    printf("m = %lld, k = %lld, p = %lld\n", m, k, p);

    long long baby_res = 0;
    long long baby_step[m];
    long long baby_dex[m];
    long long j;

    for (j = 0; j <= m - 1; j++){
        baby_res = (expo(a, j, p) * (y % p)) % p;
        baby_step[j] = baby_res;
        printf("j now:%lld, %lld\n",j, baby_res);
    }

    for (int i = 0; i < m - 1; i++) {
        baby_dex[i] = i;
    }

    for (int i = 0; i < m - 2; i++) {
        for (int j = (m - 2); j > i; j--) {
            if (baby_step[j - 1] > baby_step[j]) {
                int tmp = baby_step[j - 1];
                baby_step[j - 1] = baby_step[j];
                baby_step[j] = tmp;

                tmp = baby_dex[j - 1];
                baby_dex[j - 1] = baby_dex[j];
                baby_dex[j] = tmp;
            }
        }
    }

    printf("---------------------------\n");
    long long big_res = 0;
    long long i;

    for (i = 1; i <= k; i++) {
        big_res = expo(a, (i * m), p);
        printf("big res = %lld\n", big_res);
        int left = 0;
        int right = m - 1;
        int search = -1;

        while (left <= right) {
            int mid = (left + right) / 2;
            if (big_res == baby_step[mid]) {
                search = mid;
                break;
            }
            if (big_res  < baby_step[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
           
        }
        if (search == -1)
            printf("UIYG\n");
        else {
            printf("baby step result = %lld, index baby step = %lld\n", baby_step[search], baby_dex[search]);
            x = baby_dex[search] * m - i;
            printf("x = %lld\n", x);
            
            int c = expo(a, x, p);
            printf("Check = %d\n", c);
        }
    }



/*    for (j = 0; j <= m - 1; j++) {
        for (i = 1; i <= k; i++) {
            printf("j now:%lld ,%lld;i now:%lld, %lld\n",j, baby_step[j], i, big_step[i]);
            if (baby_step[j] == big_step[i]) {
                
                x = i * m - j;
                printf("Result: %lld\n", x);
            }
        }
    }*/

    return 0;
}

long long expo(long long a, long long x, long long p) {
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
