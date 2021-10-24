#ifndef ALENOV_BSE204_AVS_2_CYCLICSHIFT_H
#define ALENOV_BSE204_AVS_2_CYCLICSHIFT_H

#include "text.h"
#include <fstream>

using std::to_string;

//---------------------------------------------------------------------------
// cyclicShift.h - содержит наследованный от text класс cyclicShift.
//---------------------------------------------------------------------------

class cyclicShift : public text {
public:
    // Переменная n отвечает за длину сдвига при шифровании.
    int n = 0;

    void In(ifstream &ifst) override {
        ifst >> n;
        string input;
        while (ifst >> input) {
            if (input == ";") {
                break;
            }
            message += input + " ";
        }
        Encrypt();
    }

    void InRnd() override {
        message = Random();
        RandEncrypt();
    }

    void Encrypt() override {
        encrypted += "(n = " + to_string(n) + ") ";
        for (char i : message) {
            if (i == ' ') {
                encrypted += ' ';
            } else {
                encrypted += (char) ((int) i + n);
            }
        }
        // Заполняем значение частного.
        Quotient();
    }

    void RandEncrypt() {
        n = rand() % 10 + 1;
        encrypted += "(n = " + to_string(n) + ") ";
        for (char i: message) {
            if (i == ' ') {
                encrypted += ' ';
            } else {
                encrypted += (char) ((int) i + n);
            }
        }
        // Заполняем значение частного.
        Quotient();
    }

    // Перепись вывода в файл родительского класса.
    void Out(ofstream &ofst) override{
        ofst << "Text: " << message
             << "\nEncryption by cyclically shifting the code of each character by "<<n<<": " << encrypted << "\n";
    }
};

#endif //ALENOV_BSE204_AVS_2_CYCLICSHIFT_H
