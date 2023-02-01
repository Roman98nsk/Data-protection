#include "lab-2.hpp"

int main () {

    srand(time(NULL));

    string input_file = "Для презентации.pdf";
    //string input_file = "lisa.jpg";

    /*cout << "Шифр Шамира" << endl;
    Shamir_code(input_file);
    Shamir_decode();

    cout << "Шифр Эль-Гамаля" << endl;
    El_Gamala_coding(input_file);
    El_Gamala_decoding();

    cout << "Шифр Вернама" << endl;
    Vernam_coding(input_file);
    Vernam_decoding();*/

    cout << "Шифр RSA" << endl;
    RSA_coding(input_file);
    RSA_decoding();

    return 0;
}