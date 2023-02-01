#include "lab-1.hpp"

//   Функция быстрого возведения числа в степень по модулю
//   a^x(mod p) = y
long long modulo_multiplication(long long a, long long x, long long p) 
{
    long long r;
    long long y = 1;
 
    while (x > 0)
    {
        r = x % 2;
        x = x / 2;
        // fast exponention
        if (r == 1) {
            y = (y*a) % p;
        }
        a = a*a % p;
    }
 
    return y;

}

//   алгоритм Евклида
//   ax + by = nod(a,b)
//int gcd_Evclid(int a, int b, int *x, int *y) {
vector <long long> gcd_Evclid(int a, int b) {
    

    if (b > a) {
        int tmp = a;
        a = b;
       // cout << "a " << a << endl;
        b = tmp;
       // cout << "b " << b << endl;
    }

    vector <long long> u = {a, 1, 0};
    long long v[3] = {b, 0, 1};
    long long T[3] = {0, 0, 0};

    long long q = a / b;

    do {
        T[0] = u[0] % v[0];
        T[1] = u[1] - q * v[1];
        T[2] = u[2] - q * v[2];

        for (int i = 0; i <  3; i++) {
            u[i] = v[i];
            v[i] = T[i];
        }
    } while (v[0] != 0);

    return u;
}

// проверка на простое число
bool is_prime(long long p)
{
	if (p <= 1) return false;
	 
	long long b = (long long) pow(p, 0.5); 

	for(int i = 2; i <= b; i++)
	{
	  if ((p % i) == 0) return false;        
	}     
	 
   return true;    
}

long long random_prime_number(long long lower_limit, long long upper_limit) {
	long long prime_number;

	do {
	    prime_number = (long long) (rand() % (upper_limit - lower_limit) + lower_limit);
	    
	    if (prime_number % 2 == 0) {
	        prime_number += 1;
	    }
	} while (!is_prime(prime_number));
	return prime_number;
}

void getGP (long long *p, long long *g) {

    long long q;

    do {
		q = random_prime_number(1, RANGE);
		*p = 2 * q + 1;
	} while (!is_prime(*p) && !is_prime(q));
	
	do {
		*g = random_prime_number(1, *(p)-1);
	} while (modulo_multiplication(*g, q, *p) == 1);
    
}

//   алгоритм Диффи-Хеллмана
void diff_helf()
{
    long long p;
	long long q;
	long long g = 0;
	long long Xa = 0;
	long long Xb = 0;
	long long Ya = 0;
	long long Yb = 0;
	long long Za = 0;
	long long Zb = 0;

    getGP(&p, &g);

	Xa = rand() % (p - 1) + 1;
	Xb = rand() % (p - 1) + 1;

	Ya = modulo_multiplication(g, Xa, p);
	Yb = modulo_multiplication(g, Xb, p);

	Za = modulo_multiplication(Yb, Xa, p);
	Zb = modulo_multiplication(Ya, Xb, p);
	
	cout << "Data public: " << "\t\t\t" << "| Data private: " << endl;
	cout << "p = " << p << "\t\t\t" << "| Xa = " << Xa << endl;
	cout << "q = " << q << "\t\t\t" << "| Xb = " << Xb << endl;
	cout << "Ya = " << Ya << endl;
	cout << "Yb = " << Yb << endl;
	cout << "g = " << g << endl << endl;

	if (Za == Zb)
	{
		cout << "Za = Zb = " << Za << endl;
	}
	else
	{
		cout << "the answer is incorrect" << endl;
	}
}

void Shanks(long long a, long long y, long long p, long long m, long long k)
{
    srand(time(NULL));
    std::map<long long, long long> Map;
    vector<long long> x;

    long long cur_val_series = 0; // серия текущих значений
    long long I = 0;
    long long J = 0;


    // шаг младенца
    for (long long j = 0; j <= m - 1; j++) {
        cur_val_series = (modulo_multiplication(a, j, p) * y) % p;
        //cout << "cur_val_series " << cur_val_series << endl;
        Map[cur_val_series] = j; // добавляем новые эл-ты
        //cout << "Map " << Map[cur_val_series] << endl;
    }

    // шаг великана
    for (long long i = 1; i <= k; i++) {
        cur_val_series = modulo_multiplication(a, (i * m), p);
        //cout << "*cur_val_series " << cur_val_series << endl;
       // cout << "i " << i << endl;
        if(Map.count(cur_val_series)) {
           // cout << "i " << i << endl;
            I = i;
            //cout << "I " << I << endl;
            J = Map[cur_val_series];
            //cout << "J " << I << endl;
            x.push_back(I * m - J);
        }
    }

    for (auto &i:x){
        cout << i << " " << endl;
    }
}