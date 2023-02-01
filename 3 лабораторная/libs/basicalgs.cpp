#include <../libs/basicalgs.hpp>

long long int fexp(long long int base, long long int exp, long long int mod)
{
    long long int log = floor(log2(exp));
    long long int row = 0;
    long long int prod = 1;

    for (int i = 0; i <= log; i++) {
        if (i == 0)
        {
            row = base % mod;
        }
        else
        {
            row = (row * row) % mod;
        }

        if ((exp >> i) & 1)
        {
            prod = (prod * row) % mod;
        }
    }

    return prod;
}

int isPrime(int n)
{
    if (n <= 1)
    {
        return 0;
    }

    for (int i = 2; i < sqrt(n); i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }

    return 1;
}

long long gcd(long long a, long long b, long long* x, long long* y)
{
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    long long x1, y1;
    long long d = gcd(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return d;
}

int gcd(long a, long b, long* x, long* y)
{
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    long x1, y1;
    long d = gcd(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return d;
}

std::vector<int> solve(int a, int y, int m)
{
    int n = (int)sqrt(m + .0) + 1;

    std::map<int, int> vals;
    std::vector<int> result;

    for (int i = n; i >= 1; --i)
    {
        vals[fexp(a, i * n, m)] = i;
    }

    for (int i = 0; i < n; ++i)
    {
        int cur = (fexp(a, i, m) * y) % m;

        if (vals.count(cur))
        {
            int ans = vals[cur] * n - i;

            result.push_back(ans);
        }
    }

    return result;
}

int generate_numbers(long int& c, long int& d, long int p)
{
    p--;
    c = rand() % p;

    long int gcd_x, gcd_y;

    while (c < p)
    {
        if (gcd(c, p, &gcd_x, &gcd_y) == 1)
        {
            d = gcd_x;

            if ((c * d) % p == 1)
            {
                return 1;
            }
        }

        c++;
    }

    return 0;
}

long long int generate_prime_numbers(long long int& c, long long int& d, long long int p)
{
    // p--;
    c = rand() % p;

    while (!isPrime(c))
    {
        c = rand() % p;
    }

    long int gcd_x, gcd_y;

    while (c < p)
    {
        if (gcd(c, p, &gcd_x, &gcd_y) == 1)
        {
            d = gcd_x;

            if ((c * d) % p == 1)
            {
                return 1;
            }
        }

        c++;
    }

    return 0;
}

long int mul(long int a, long int b, long int p)
{
    return (a * b) % p;
}

int ShamirAlg(std::string filepath)
{
    long int x1, x2, x3, x4;
    std::ifstream file(filepath, std::ios::in | std::ios::binary);
    std::ofstream out_file("decrypt_shamir_" + filepath, std::ios::out | std::ios::app | std::ios::binary);
    srand(time(NULL));

    // Сообщение, которое мы хотим передать
    // Должно быть m < p (алгоритм усложняется, если m >= p)
    long int m = 256;

    // Генерируем простое число p
    long int p = rand() % (RAND_MAX) + 1;
    while (!isPrime(p) || p <= m)
    {
        p = rand() % (RAND_MAX) + 1;
    }
    std::cout << "p = " << p << "\n";

    // Генерируем числа Ca, Cb, Da, Db
    // Условия:std::vector<int> result;
    //      Ca * Da % p == 1
    //      Cb * Db % p == 1

    long int Ca, Cb, Da, Db;
    if (generate_numbers(Ca, Da, p) == 0)
    {
        std::cerr << "Gen nums error(a)\n";
    }

    if (generate_numbers(Cb, Db, p) == 0)
    {
        std::cerr << "Gen nums error(b)\n";
    }

    std::cout << "m = " << m << "\n";

    // Считываем побайтово с файла, шифруем и расшифровываем здесь
    while (file.read(reinterpret_cast<char*>(&m), sizeof(char))) // Читаем, пока читается
    {
        x1 = fexp(m, Ca, p);                                     // Отправитель(S) формирует открытый ключ X1 и передаёт его получателю(R)
        x2 = fexp(x1, Cb, p);                                    // R формирует открытый ключ X2 и передаёт S
        x3 = fexp(x2, Da, p);                                    // S формирует открытый ключ X3 и передаёт R
        x4 = fexp(x3, Db, p);                                    // R окончательно расшифровывает сообщение. X4 == m

        if (x4 == m)
        {
            // std::cout << "Success!\n";
            out_file.write(reinterpret_cast<char*>(&x4), sizeof(char));
        }
        else
        {
            std::cout << "OOOOPS\n";
        }
    }

    file.close();
    out_file.close();

    return 0;
}

std::string ElgamalEncrypt(std::string filepath, ElgamalKeys& keys)
{
    std::ifstream file(filepath, std::ios::in | std::ios::binary);
    std::ofstream out_file("encrypt_elgamal_" + filepath, std::ios::out | std::ios::app | std::ios::binary);

    long int m = 1;
    long int e = 1;
    int i = 1;

    std::cout << "e=" << sizeof(e) << '\n';
    std::cout << "m=" << sizeof(m) << '\n';
    std::cout << "i=" << sizeof(i) << '\n';

    while (file.read(reinterpret_cast<char*>(&m), sizeof(char)))
    {
        e = mul(fexp(keys.d2, keys.k, keys.p), m, keys.p);
        out_file.write(reinterpret_cast<char*>(&e), sizeof(long int));
    }

    file.close();
    out_file.close();

    return std::string("encrypt_elgamal_" + filepath);
}

void ElgamalDecrypt(std::string filepath, ElgamalKeys& keys)
{
    std::ifstream file(filepath, std::ios::in | std::ios::binary);
    std::ofstream out_file("decrypt_elgamal_" + filepath.substr(16), std::ios::out | std::ios::app | std::ios::binary);

    char m;
    long int en;

    while (file.read(reinterpret_cast<char*>(&en), sizeof(long int)))
    {
        m = mul(en, fexp(keys.r, keys.p - 1 - keys.c2, keys.p), keys.p);
        out_file.write(reinterpret_cast<char*>(&m), sizeof(char));
    }

    file.close();
    out_file.close();
}

void ElgamalInit(ElgamalKeys& keys)
{
    srand(time(NULL));
    // Генерируем простое число p. +6, чтобы правильно сгенерировать c1,c2
    keys.p = rand() % (RAND_MAX) + 6;

    while (!isPrime(keys.p) || keys.p <= 256)
    {
        keys.p = rand() % (RAND_MAX) + 1;
    }

    // Вычисляем g: p/2 < g < p-1 (ВРОДЕ БЫ)
    keys.g = keys.p / 2 + 1;

    // Генерируем секретные числа 1 < c < p-1
    keys.c1 = (rand() % (keys.p - 2)) + 2;
    keys.c2 = (rand() % (keys.p - 2)) + 2;

    // Открытые ключи
    keys.d1 = fexp(keys.g, keys.c1, keys.p);
    keys.d2 = fexp(keys.g, keys.c2, keys.p);

    // A вычисляет
    keys.k = (rand() % (keys.p - 3)) + 2;
    keys.r = fexp(keys.g, keys.k, keys.p);
}

void VernamAlg(std::string filepath)
{
    std::ifstream file(filepath, std::ios::in | std::ios::binary);
    std::ofstream out_file("decrypt_vernam_" + filepath, std::ios::out | std::ios::binary);

    char oStr;                      //открытый текст(который шифруем)
    char shStr;                     //зашифрованного текст
    char deStr;                     //расшифрованный текст
    char key = (char)rand() % 255;  //ключ

    //само шифрование
    while (file.read(reinterpret_cast<char*>(&oStr), sizeof(char)))
    {
        shStr = oStr ^ key;
        deStr = shStr ^ key;

        out_file.write(reinterpret_cast<char*>(&deStr), sizeof(char));
    }
}

void RSAAlg(std::string filepath)
{
    srand(time(NULL));

    std::ifstream file(filepath, std::ios::in | std::ios::binary);
    std::ofstream out_file("decrypt_RSA_" + filepath, std::ios::out | std::ios::app | std::ios::binary);

    long long int P = rand() % 10000+16;//(RAND_MAX) + 1;
    while (!isPrime(P))
    {
        P = rand() % 10000+16;//(RAND_MAX) + 1;
    }

    long int Q = rand() % 10000+16;//(RAND_MAX) + 1;
    while (!isPrime(Q))
    {
        Q = rand() % 10000+16;//(RAND_MAX) + 1;
    }

    long long int N = P * Q;

    long long int phi = (P - 1) * (Q - 1);

    long long int d, c;

    std::cout << generate_prime_numbers(c, d, phi) << "\n\n\n";
    // generate_prime_numbers(d, c, phi - 1);
    std::cout << fexp(d * c, 1, phi) << "\n\n\n";
    std::cout << d << "\n\n\n";
    std::cout << c << "\n\n\n";
    std::cout << phi << "\n\n\n";
    // c * d % phi = 1

    // e = m^d % n;
    long long int e;
    char m_ = 0;
    char m = 42;

    while (file.read(reinterpret_cast<char*>(&m), sizeof(char)))
    {
        e = fexp(m, d, N);
        m_ = fexp(e, c, N);
        out_file.write(reinterpret_cast<char*>(&m_), sizeof(char));
    }
}

long take_hash(std::vector<char>& msg)
{
    long y = 0;

    for (auto &m: msg)
    {
        y += m;
    }

    y = y % (long)pow(2, 64);

    return y;
}

void RSA_Get_keys(RSA_Open_key& open_key, RSA_Secret_key& secret_key)
{
    srand(time(NULL));

    long long int p = rand() % 10000+16;
    while (!isPrime(p))
    {
        p = rand() % 10000+16;
    }

    long int q = rand() % 10000+16;
    while (!isPrime(q))
    {
        q = rand() % 10000+16;
    }

    open_key.n = p * q;

    long long int phi = (p - 1) * (q - 1);

    generate_prime_numbers(secret_key, open_key.d, phi);
}

RSA_Signed_msg RSA_Sign_msg(std::vector<char>& msg, RSA_Open_key open_key, RSA_Secret_key secret_key)
{
    auto y = take_hash(msg);

    auto s = fexp(y, secret_key, open_key.n);

    RSA_Signed_msg e {msg, s};

    return std::move(e);
}

bool RSA_Check_msg(RSA_Signed_msg& e, RSA_Open_key open_key)
{
    long long y = take_hash(e.data);
    long long w = fexp(e.s, open_key.d, open_key.n);

    return w == y;
}


long int get_inverse(long long int& c, long long int p) 
{
    long long int d;
    long asd;
    long long int gcd_x, gcd_y;
    p--;
    while (c < p) {
        if (gcd(c, p, &gcd_x, &gcd_y) == 1) {
            d = gcd_x;
            asd = gcd_x;
            if ((c * d) % p == 1) {
                return asd;
            }
        }
        c++;
    }
    return -1;
}

void Elgamal_Get_keys(Elgamal_Open_key& open_key, Elgamal_Secret_key& secret_key)
{
    srand(time(NULL));

    open_key.p = rand() % (RAND_MAX);

    while (!isPrime(open_key.p))
    {
        open_key.p = rand() % (RAND_MAX);
    }

    open_key.g = open_key.p / 2 + 1;

    secret_key = (rand() % (open_key.p - 2)) + 2;

    open_key.y = fexp(open_key.g, secret_key, open_key.p);
}

Elgamal_Signed_msg Elgamal_Sign_msg(std::vector<char>& msg, Elgamal_Open_key& open_key, Elgamal_Secret_key secret_key)
{
    long h = take_hash(msg);
    long long k_;
    long long k;

    generate_prime_numbers(k, k_, open_key.p - 1);
    long r = fexp(open_key.g, k, open_key.p);
    long long u = h - secret_key * r % (open_key.p - 1) + (open_key.p - 1);
    long long s = (k_ * u) % (open_key.p - 1);

    Elgamal_Signed_msg e { msg, s, r };

    return std::move(e);
}

bool Elgamal_Check_msg(Elgamal_Signed_msg& e, Elgamal_Open_key open_key)
{
    auto h = take_hash(e.data);
    long long lhs = (fexp(open_key.y, e.r, open_key.p) * fexp(e.r, e.s, open_key.p)) % open_key.p;
    long long rhs = fexp(open_key.g, h, open_key.p);

    return lhs == rhs;
}

void Gost_Get_keys(Gost_Open_keys& keys, pint& x, std::vector<char>& msg)
{
    std::time_t now = std::time(0);
    r::mt11213b gen_test(now);
    generator1024_type gen1024(now);
    generator256_type gen256(now);

    keys.q = gen256();
    pint b = gen256();
    keys.p = b * keys.q + 1;
    pint hash = take_hash_pint(msg);
    pint hash_ = 0;
    pint buff;

    while (!(mp::miller_rabin_test(static_cast<upint>(keys.q), 25, gen_test) && mp::miller_rabin_test(static_cast<upint>(keys.p), 25, gen_test) && (((hash * hash_) % keys.q) == 1))) {
        keys.q = gen256();
        b = gen256();
        keys.p = b * keys.q + 1;
        gcd(hash, keys.q, &hash_, &buff);
    }

    pint g = gen256();
    do {
		keys.a = mod_pow(g, (keys.p - 1) / keys.q, keys.p);
        g++;
	} while(mod_pow(keys.a, keys.q, keys.p) != 1);

    x = gen256() % keys.q;
    keys.y = mod_pow(keys.a, x, keys.p);
}

Gost_Signed_msg Gost_Sign_msg(std::vector<char>& msg, Gost_Open_keys keys, pint x)
{
    std::time_t now = std::time(0);
    r::mt11213b gen_test(now);
    generator1024_type gen1024(now);
    generator256_type gen256(now);
    pint hash = take_hash_pint(msg);
    pint r = 1;
    pint k = 0;
    pint s;
    while (r == 0 || s == 0) {
        k = gen256() % keys.q;
        k = 8;
        r = mod_pow(keys.a, k, keys.p) % keys.q;
        
        s = ((k * hash) + (x * r)) % keys.q;
    }

    Gost_Signed_msg e {msg, r, s};

    return std::move(e);
}

bool Gost_Check_msg(Gost_Signed_msg e, Gost_Open_keys keys)
{
    pint hash = take_hash_pint(e.data);
    pint hash_;
    pint buff;
    gcd(hash, keys.q, &hash_, &buff);
    pint u1 = ((e.s % keys.q) * (hash_ % keys.q)) % keys.q;
    pint u2 = (-e.r * hash_) % keys.q + keys.q;
    pint v = ((mod_pow(keys.a, u1, keys.p) * mod_pow(keys.y, u2, keys.p)) % keys.p) % keys.q;

    return v == e.r;
}

pint gcd(pint a, pint b, pint* x, pint* y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    pint x1, y1;
    pint d = gcd(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return d;
}

pint mod_pow(pint num, pint degree, pint p)
{
	pint result = 1;
	for(; degree; num = num * num % p, degree >>= 1) {
		if(degree & 1) {
			result = result * num % p;
		}
	}

	return result;
}

pint take_hash_pint(std::vector<char>& msg)
{
    pint y = 0;

    for (auto &m: msg)
    {
        y += m;
    }

    y = y % (pint)pow(2, 64);

    return y;
}