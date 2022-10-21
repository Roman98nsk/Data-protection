#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    long long int m = 0, k = 0, e = 0, c = 1, count = 0;
    srand(time(NULL));

    m = 2 + rand() % 10;

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
    m = e ^ k;
    printf("m decode = %lld\n", m);
    return 0;
}