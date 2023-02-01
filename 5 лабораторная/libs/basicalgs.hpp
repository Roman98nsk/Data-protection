#pragma once

#include <algorithm>
#include <cmath>
#include <map>
#include <iterator>
#include <string>
#include <map>
#include <ctime>
#include <functional>
#include <fstream>
#include <iostream>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/random.hpp>
#include "structs.hpp"

long greatestCommonDivisor(long e, long t);
long calculateE(long t);
long fexp(long base, long exp, long mod);
int isPrime(int n);
long gcd(long a, long b, long* x, long* y);
//int gcd(long a, long b, long* x, long* y);
std::vector<int> solve(int a, int y, int m);
int generate_numbers(long& c, long& d, long p);
long generate_prime_numbers(long& c, long& d, long p);
long mul(long a, long b, long p);
int ShamirAlg(std::string filepath);
std::string ElgamalEncrypt(std::string filepath, ElgamalKeys& keys);
void ElgamalDecrypt(std::string filepath, ElgamalKeys& keys);
void ElgamalInit(ElgamalKeys& keys);
void VernamAlg(std::string filepath);
void RSAAlg(std::string filepath);

long take_hash(std::vector<char>& msg);
void RSA_Get_keys(RSA_Open_key& open_key, long& secret_key);
RSA_Signed_msg RSA_Sign_msg(std::vector<char>& msg, RSA_Open_key open_key, long secret_key);
bool RSA_Check_msg(RSA_Signed_msg& e, RSA_Open_key open_key);
long get_inverse(long& c, long p);
void Elgamal_Get_keys(Elgamal_Open_key& open_key, long& secret_key);
Elgamal_Signed_msg Elgamal_Sign_msg(std::vector<char>& msg, Elgamal_Open_key& open_key, long secret_key);
bool Elgamal_Check_msg(Elgamal_Signed_msg& e, Elgamal_Open_key open_key);
void Gost_Get_keys(Gost_Open_keys& keys, pint& x, std::vector<char>& msg);
Gost_Signed_msg Gost_Sign_msg(std::vector<char>& msg, Gost_Open_keys keys, pint x);
bool Gost_Check_msg(Gost_Signed_msg e, Gost_Open_keys keys);
pint gcd(pint a, pint b, pint* x, pint* y);
pint mod_pow(pint num, pint degree, pint p);
pint take_hash_pint(std::vector<char>& msg);

std::string find_key_by_value(std::map<std::string, long >& mp, long id);
bool find_key_by_fexp(std::map<std::string, long>& mp, long value, long p, long ca);
long generate_prime_numbers_v2 (long& c, long& d, long p);
upint gcd(upint a, upint b, upint* x, upint* y);