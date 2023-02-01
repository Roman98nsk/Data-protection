#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>

namespace mp = boost::multiprecision;
namespace r = boost::random;

typedef boost::multiprecision::int1024_t pint;
typedef boost::multiprecision::uint1024_t upint;
typedef boost::multiprecision::uint512_t uint512;
typedef boost::multiprecision::uint256_t qint;
typedef boost::multiprecision::int256_t sqint;
typedef r::independent_bits_engine<r::mt19937, 1024, mp::int1024_t> generator1024_type;
typedef r::independent_bits_engine<r::mt19937, 1024, mp::uint1024_t> generator1024_utype;
typedef r::independent_bits_engine<r::mt19937, 512, mp::uint512_t> generator512_utype;
typedef r::independent_bits_engine<r::mt19937, 256, mp::int256_t> generator256_type;
typedef r::independent_bits_engine<r::mt19937, 256, mp::uint256_t> generator256_utype;

struct ElgamalKeys
{
    long p, g, c1, c2, d1, d2, k, r;
};

struct RSA_Open_key
{
    long n, d;
};

struct Elgamal_Open_key
{
    long y, p, g;
};

struct RSA_Signed_msg
{
    std::vector<char> data;
    long s;
};

struct Elgamal_Signed_msg
{
    std::vector<char> data;
    long s, r;
};

struct Gost_Open_keys
{
    pint q, p, y, a;
};

struct Gost_Signed_msg
{
    std::vector<char> data;
    pint r, s;
};