//------------------------------------------------------------------------------------
// charecterReplacement.h - содержит наследованный от text класс charecterReplacement.
//------------------------------------------------------------------------------------

#ifndef ALENOV_BSE204_AVS_2_CHARECTERREPLACEMENT_H
#define ALENOV_BSE204_AVS_2_CHARECTERREPLACEMENT_H

#include "text.h"
#include <fstream>

using std::to_string;

class charecterReplacement: public text {
public:
    void Encrypt() override{
        // Изначальный алфавит.
        string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        // Алфавит для шифровки.
        string encryptCode = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
        for (char i : message) {
            if (i == ' ') {
                encrypted += " ";
            } else {
                if (alphabet.find(i) != std::string::npos){
                    encrypted += encryptCode[alphabet.find(i)];
                } else {
                    encrypted += i;
                }
            }
        }
        // Заполняем значение частного.
        Quotient();
    }
    // Перепись вывода в файл родительского класса.
    void Out(ofstream &ofst) override{
        ofst << "Text: " << message
             << "\nEncryption by substitution of characters: " << encrypted << "\n";
    }
};

#endif //ALENOV_BSE204_AVS_2_CHARECTERREPLACEMENT_H
