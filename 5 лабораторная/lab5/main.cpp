#include "basicalgs.cpp"

unsigned long secure_pipe;
unsigned long sc_n;
unsigned long sc_s;

struct PublicKeys {
    unsigned long N, D;
};

class Server {
private:
    unsigned long P, Q;
    unsigned long C;
    uint8_t tag;

public:
    Server(PublicKeys &keys)
    {
        P = rand() % UINT16_MAX; //(RAND_MAX) + 1;
        while (!isPrime(P)) {
            P = rand() % UINT16_MAX; //(RAND_MAX) + 1;
        }

        Q = rand() % UINT16_MAX; //(RAND_MAX) + 1;
        while (!isPrime(Q)) {
            Q = rand() % UINT16_MAX; //(RAND_MAX) + 1;
        }

        keys.N = P * Q;
        unsigned long phi = (P - 1) * (Q - 1);
        tag = 0;

        generate_prime_numbers_v2(C, keys.D, phi);

        std::cout << "N = " << keys.N << "\n";
        std::cout << "D = " << keys.D << "\n";
    }

    void h_to_s(PublicKeys keys)
    {
        tag = 1;
        secure_pipe = mod_pow(secure_pipe, C, keys.N);
    }

    void check_sign(PublicKeys keys)
    {
        unsigned long ss = mod_pow(sc_s, keys.D, keys.N);
        std::cout << "ss = " << ss << "\n";
    }
};

class Alice {
private:
    unsigned long rnd;
    unsigned long u;
    unsigned long n;
    unsigned long r;
    unsigned long r_;
    unsigned long h;
    unsigned long s;

public:

    Alice(PublicKeys keys)
    {
        rnd = rand() % UINT16_MAX;
        u = 1;
        n = std::stol(std::to_string(rnd) + std::to_string(u));

        // r = rand() % 1000 + 16;
        // unsigned long x, y;

        // while (gcd(r, keys.N, &x, &y) != 1) {
        //     r = rand() % 1000 + 16;
        // }

        generate_prime_numbers_v2(r, r_, keys.N);

        h = n;

        std::cout << "r * r_ mod N = " << ((r % keys.N) * (r_ % keys.N)) % keys.N << "\n";
        std::cout << "rnd = " << rnd << "\n";
        std::cout << "u = " << u << "\n";
        std::cout << "n = " << n << "\n";
        std::cout << "r = " << r << "\n";
        std::cout << "h = " << h << "\n";
    }

    void send_h_(PublicKeys keys)
    {
        secure_pipe = ((h % keys.N) * mod_pow(r, keys.D, keys.N)) % keys.N;
    }

    void sign_bulletin(PublicKeys keys)
    {
        //unsigned long x;
        //gcd(r, keys.N, &r_, &x);
        std::cout << "r_ = " << r_ << "\n";
        s = ((secure_pipe % keys.N) * (r_ % keys.N)) % keys.N;
        std::cout << "s = " << s << "\n";
    }

    void send_sing()
    {
        sc_s = s;
        sc_n = n;
    }
};

int main()
{
    srand(time(NULL));
    PublicKeys keys;
    Server server(keys);
    Alice alice(keys);

    alice.send_h_(keys);
    std::cout << "h_ = " << secure_pipe << "\n";
    server.h_to_s(keys);
    std::cout << "s_ = " << secure_pipe << "\n";

    alice.sign_bulletin(keys);
    alice.send_sing();

    server.check_sign(keys);

    // std::time_t now = std::time(0);
    // generator512_utype gen512(now);
    // uint512 test1 = gen512();
    // uint512 test2 = gen512();
    // upint test = 0;
    // test = test | (test1 << 511);
    // test = test | test2;

    // std::cout << "test1 = " << test1 << "\n";
    // std::cout << "test2 = " << test2 << "\n";
    // std::cout << "test = " << test << "\n";


    // std::cout << "N = " << keys.N << "\n";
    // std::cout << "D = " << keys.D << "\n";
    // unsigned long P, Q;

    // P = rand() % 10000 + 16; //(RAND_MAX) + 1;
    // while (!isPrime(P)) {
    //     P = rand() % 10000 + 16; //(RAND_MAX) + 1;
    // }

    // Q = rand() % 10000 + 16; //(RAND_MAX) + 1;
    // while (!isPrime(Q)) {
    //     Q = rand() % 10000 + 16; //(RAND_MAX) + 1;
    // }

    // unsigned long N = P * Q;

    // std::cout << "N = " << N << "\n";
    // std::cout << "P = " << P << "\n";
    // std::cout << "Q = " << Q << "\n";

    // unsigned long C, D;
    // unsigned long phi = (P - 1) * (Q - 1);

    // generate_prime_numbers(C, D, phi);

    // std::cout << "C * D mod phi = " << C * D % phi << "\n";

    // unsigned long rnd = rand() % 10000 + 16;
    // unsigned long u = 1;
    // unsigned long n = std::stoi(std::to_string(rnd) + std::to_string(u));

    // std::cout << "rnd = " << rnd << "\n";
    // std::cout << "u = " << u << "\n";
    // std::cout << "n = " << n << "\n";

    // unsigned long r = rand() % 10000 + 16;
    // // unsigned long b = 3;
    // unsigned long x, y;

    // while (gcd(r, N, &x, &y) != 1) {
    //     r = rand() % 10000 + 16;
    // }

    // std::cout << "r = " << r << "\n";
    // // std::cout << "test = " << gcd(r, N, &x, &y) << "\n";

    // unsigned long h = n;

    // unsigned long h_ = (mod_pow(h, 1, N) * mod_pow(r, D, N)) % N;

    // std::cout << "h = " << h << "\n";
    // std::cout << "h_ = " << h_ << "\n";

    // unsigned long s_ = mod_pow(h_, C, N);

    // std::cout << "s_ = " << s_ << "\n";

    // unsigned long r_;
    // gcd(r, N, &r_, &x);
    // std::cout << "r_ = " << r_ << "\n";

    // unsigned long s = ((s_ % N) * (r_ % N)) % N;
    // std::cout << "s = " << s << "\n";

    // // unsigned long ss = (mod_pow(h, C, N) * mod_pow(r, D * C, N) * r_) % N;
    // unsigned long ss = mod_pow(s, D, N);
    // std::cout << "ss = " << ss << "\n";

    return 0;
}