#include "lab-1.hpp"

int main () {
    srand(time(NULL));
    // 1
    
    // long long a(5), x(11), p(12);
    
    /*long long a = rand() % RANGE;
    long long x = rand() % RANGE;
    long long p = rand() % RANGE;
    
    long long result = modulo_multiplication(a, x, p);
    cout << a << "^" << x << " mod " << p << " = " << result << endl;*/

    // 2
    //int b = 35, a = 15;
    
    long long b = rand() % RANGE;
    long long c = rand() % RANGE;
    
    //long long g = gcd_Evclid(b, c);

    // 3
   // diff_helf();
    // 4
    //long long p = 7;
    //long long a = 5;
    //long long y = 4;
    long long m;
    long long k;
    long long p;
    long long g;
	long long a;
	long long y;

    do {
        p = rand() % 1000000 + 1;
        a = rand() % 1000000 + 1;
    } while(gcd_Evclid(p, a) [0] == 1);

        y = rand() % 1000000 + 1;
        m = (long long)sqrt(p) + 1;
        k = (long long)sqrt(p) + 1;
        //cout << "*" << endl;

    Shanks(a, y, p, m, k);

    return 0;
}