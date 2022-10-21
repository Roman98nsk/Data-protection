#ifndef MAIN_H
#define MAIN_H

int El_Gamal();
int RSA();
int Shamir();
int Vernam();

bool isPrime(long long int n);
long long int expo(long long int a, long long int x, long long int p);
long long int gcd(long long int n1, long long int n2);
long long int Euclid(long long int a, long long int b);

#endif /*MAIN_H*/