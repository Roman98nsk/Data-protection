#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "basicalgs.cpp"

int main() {
    srand(time(NULL));
    long p = rand() % (RAND_MAX) + 1;  // модуль
    long g = rand() % (RAND_MAX) + 1;  // база
    printf("p=%ld\n", p);
    printf("g=%ld\n", g);
    while (g >= p) {
        g = rand() % (RAND_MAX) + 1;
    }

    long a, b;  // `a` – секретный ключ Алисы, `b` – секретный ключ Боба.
    long A, B;  // `A` – открытый ключ Алисы, `B` – открытый ключ Боба

    // выбираем секретное целое число для закрытого ключа Алисы (известного только Алисе)
    a = rand() % (RAND_MAX) + 1;  // или используйте `rand()`
    printf("a=%ld\n", a);

    // Вычисление открытого ключа Алисы (Алиса отправит Бобу `A`)
    A = fexp(g, a, p);
    printf("A=%ld\n", A);
    // выбираем секретное целое число для закрытого ключа Боба (известного только Бобу)
    b = rand() % (RAND_MAX) + 1;  // или используйте `rand()`
    printf("b=%ld\n", b);
    // Вычислить открытый ключ Боба (Боб пошлет `B` Алисе)
    B = fexp(g, b, p);
    printf("B=%ld\n", B);
    // Алиса и Боб обмениваются своими открытыми ключами `A` и `B` друг с другом

    // Находим секретный ключ
    long int keyA = fexp(B, a, p);
    long int keyB = fexp(A, b, p);
    printf("KEYA=%ld\n", keyA); // <---|
                                //      --------   Ключи ДОЛЖНЫ совпадать   
    printf("KEYBA=%ld\n", keyB);// <---|
    printf("Alice's secret key is %ld\nBob's secret key is %ld\n", keyA, keyB);

    return 0;
}