#include "basicalgs.cpp"

#include <vector>
#include <iostream>

int main() {

    std::vector<char> msg {'h', 'e', 'l', 'l', 'o'};

    Elgamal_Open_key ok1, ok2;
    long sk;
    ok2.g = 356;
    ok2.p = 1464;
    ok2.y = 58;

    Elgamal_Get_keys(ok1, sk);

    auto signed_msg = Elgamal_Sign_msg(msg, ok1, sk);

    std::cout << "1) " << Elgamal_Check_msg(signed_msg, ok1) << "\n";
    std::cout << "2) " << Elgamal_Check_msg(signed_msg, ok2) << "\n";

    return 0;
}
