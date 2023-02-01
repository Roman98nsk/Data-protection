#include "basicalgs.cpp"

#include <vector>
#include <iostream>

int main() {

    std::vector<char> msg {'h', 'e', 'l', 'l', 'o'};

    RSA_Open_key ok1, ok2;
    long sk;

    RSA_Get_keys(ok1, sk);

    auto signed_msg = RSA_Sign_msg(msg, ok1, sk);

    ok2.n = 13;
    ok2.d = 45;
    for(auto& item : signed_msg.data)
        std::cout << item << "\n";

    std::cout << signed_msg.s << "\n";
    std::cout << "1) " << RSA_Check_msg(signed_msg, ok1) << "\n";
    std::cout << "2) " << RSA_Check_msg(signed_msg, ok2) << "\n";

    return 0;
}
