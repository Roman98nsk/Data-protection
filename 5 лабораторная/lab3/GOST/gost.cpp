#include <time.h>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>

#include "basicalgs.cpp"

int main() 
{
    std::vector<char> msg = {'h', 'e', 'l', 'l', 'o'};
    Gost_Open_keys keys;
    
    pint secret_key;
    pint secret_key_test = 234567890;

    Gost_Get_keys(keys, secret_key, msg);

    auto signed_msg = Gost_Sign_msg(msg, keys, secret_key);
    auto signed_msg_test = Gost_Sign_msg(msg, keys, secret_key_test);

    std::cout << Gost_Check_msg(signed_msg, keys) << "\n";
    std::cout << Gost_Check_msg(signed_msg_test, keys) << "\n";

    return 0;
}
