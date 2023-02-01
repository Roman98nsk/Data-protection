#include <iostream>
#include <string>

int main()
{
    std::cout << "int = " << sizeof(int) << "\n";
    std::cout << "long = " << sizeof(long) << "\n";
    std::cout << "long int = " << sizeof(long int) << "\n";
    std::cout << "long long int = " << sizeof(long long int) << "\n";
    std::cout << "long long = " << sizeof(long long) << "\n";

    std::string a = "";

    if (a.size()) {
        std::cout << a << "\n";
    }

    return 0;
}