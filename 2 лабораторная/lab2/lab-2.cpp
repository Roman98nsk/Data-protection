#include "lab-2.hpp"

void find (long long *c, long long *d, long long p) 
{
        while (1) {
            *c = random_prime_number(2, 1000);
            *d = random_prime_number(2, 1000);
            if (((*c) * (*d)) % (p - 1) == 1) {
                break;
        }
    }
}

long long Shamir_code (string file_name) 
{
    ofstream file_keys;
    string data = read_dec(file_name);

    long long x1, x2, *x3 = new long long[data.length()];
    long long Ca;
    long long Da;
    long long Cb;
    long long Db;
    long long p;

    while (1){
        p = rand() % 1000 + 1;  
        find(&Ca, &Da, p);
        find(&Cb, &Db, p);

        if ( Da < p && Db < p && is_prime(p)){
            break;
        }
    }    

	file_keys.open("key.txt", ios::binary);
	file_keys << p << " " << Db << endl;
	file_keys.close();

    for (uint64_t i = 0; i < data.length(); i++) {
        x1 = modulo_multiplication(data[i], Ca, p);
        x2 = modulo_multiplication(x1, Cb, p);
        x3[i] = modulo_multiplication(x2, Da, p);
    }

    write_enc("code.txt", x3, data.length());
	delete []x3;
}

long long Shamir_decode () {

	uint64_t length;
	long long *dec = read_enc("code.txt", &length);
	long long p, Db;

	ifstream file_key;
	file_key.open("key.txt", ios::binary);
	file_key >> p >> Db;
	file_key.close();

	for(uint64_t i = 0; i < length; ++i) {
		dec[i] = modulo_multiplication(dec[i], Db, p);
        //x4[i] = modulo_multiplication(x3[i], Db, p);
	}

	write_dec("decode.pdf", dec, length);
	delete []dec;
}

void El_Gamala_coding(string file_name)
{
    ofstream file_keys;
    string data = read_dec(file_name);

    long long p, g, Cb, Db, k, r, *e = new long long [data.length()];

    while (1) {
        p = rand() % RANGE + 1;
        g = rand() % RANGE + 1;
        Cb = random_prime_number(1, p-1);
        k = random_prime_number(1, p-2);

        if (is_prime(p) && (g > 1) && (g < p-1) && (Cb > 1) && (Cb < p-1)  && (1 <= k) && (k <= p-2)) {
            break;
        }
    }

    for (uint64_t i = 0; i < data.length(); i++) {
        Db = modulo_multiplication(g, Cb, p);
        r = modulo_multiplication(g, k, p);
        e[i] = (modulo_multiplication(Db, k, p) * data[i]) % p;
    }

    file_keys.open("key.txt", ios::binary);
	file_keys << p << " " << Cb << " " << r << endl;
	file_keys.close();

    write_enc("code.txt", e, data.length());
	delete []e;
}

void El_Gamala_decoding()
{
	uint64_t length;
	long long *dec = read_enc("code.txt", &length);
	long long p, Cb, r;

	ifstream file_key;
	file_key.open("key.txt", ios::binary);
	file_key >> p >> Cb >> r;
	file_key.close();

	for(uint64_t i = 0; i < length; ++i) {
		dec[i] = (modulo_multiplication(r, (p - 1 - Cb), p) * dec[i]) % p;
	}

	write_dec("decode.pdf", dec, length);
	delete []dec;
}

long long Vernam_coding(string file_name)
{
    ofstream file_keys;
    string data = read_dec(file_name);

    long long *m = new long long [data.length()];
    long long *k = new long long [data.length()];

    file_keys.open("key.txt", ios::binary);

    for (uint64_t i = 0; i < data.length(); i++) {
        k[i] = rand() % 255;
	    file_keys << k[i] << " ";    
        m[i] = data[i]^k[i];
    }

    file_keys.close();

    write_enc("code.txt", m, data.length());
	delete []m;
}

long long Vernam_decoding()
{
	uint64_t length;
	long long *dec = read_enc("code.txt", &length);
	long long *k = new long long [sizeof(long long)*length];

	ifstream file_key;
	file_key.open("key.txt", ios::binary);
	
	for(uint64_t i = 0; i < length; ++i) {
        file_key >> k[i];
		dec[i] = dec[i]^k[i];
	}
    file_key.close();

	write_dec("decode.pdf", dec, length);
	delete []dec;
}

void RSA_coding(string file_name)
{
    ofstream file_keys;
    string data = read_dec(file_name);

    long long *e = new long long [data.length()];
    long long p, q, Nb, fi, Db, Cb;

    while (1) {
        p = rand() % 1000 + 1;
        q = rand() % 1000 + 1;

        Nb = p * q;
        fi = (p-1)*(q-1);

        Db = rand() % 1000 + 1;
        Cb = rand() % 1000 + 1;

        if (is_prime(p) && is_prime(q) && (Db < fi) && is_prime(Db) && (((Cb * Db) % fi) == 1)) {
            break;
        }
    }  

    file_keys.open("key.txt", ios::binary);
	file_keys << Cb << " " << Nb << endl;
	file_keys.close();

    for (uint64_t i = 0; i < data.length(); i++) {
        e[i] = modulo_multiplication(data[i], Db, Nb);
    }

    write_enc("code.txt", e, data.length());
	delete []e;
}

void RSA_decoding()
{
    uint64_t length;
	long long *dec = read_enc("code.txt", &length);
	long long Cb, Nb;

	ifstream file_key;
	file_key.open("key.txt", ios::binary);
	file_key >> Cb >> Nb;
	file_key.close();

	for(uint64_t i = 0; i < length; ++i) {
		dec[i] = modulo_multiplication(dec[i], Cb, Nb);
	}

	write_dec("decode.pdf", dec, length);
	delete []dec; 
}