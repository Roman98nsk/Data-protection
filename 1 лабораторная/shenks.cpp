#include <iostream>
#include <map>
#include <cmath>
using namespace std;

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

long long Shanks() {
    long long p = 0, y = 0, cur_val_series = 0;

    map<long long, long long> Map;

    srand(time(NULL));
    
    long long a = 2 + rand() % 100;

    do {
        p = 2 + rand() % 100;
        y = 2 + rand() % p;
    } while (!(y < p));

    cout << "p = " << p << ", y = " << y << ", a = " << a << endl;

    long long m = (long long)sqrt(p) + 1;
    long long k = m;

    cout << "m = " << m << ", k = " << k << endl;

    long long I = 0;
    long long J = 0;
    long long x = 0;

    for (long long j = 0; j < m - 1; j++) {
        cur_val_series = (expo(a, j, p) * (y % p)) % p;
        Map[cur_val_series] = j;
    }

    for (long long i = 1; i < k; i++) {
        cur_val_series = expo(a, (i * m), p);

    if(Map.count(cur_val_series) > 0) {
        I = i;
        J = Map[cur_val_series];
        x = I * m - J;
        break;
    }
    }

    if (x == -1) {
        cout << "no equal members found"<< endl;
    } else {
        long long res_y = expo(a, x, p);
        cout << "x = " << x << endl;
        cout << "y = "<< res_y << endl;
        
        if (res_y == y) {
            cout << "good" << endl;
        }
    }
return x;
}

int main() {
    Shanks();
}