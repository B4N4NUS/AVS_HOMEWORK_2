//------------------------------------------------------------------------------
// charecterToNumber.h - содержит наследованный от text класс charecterToNumber.
//------------------------------------------------------------------------------

#ifndef ALENOV_BSE204_AVS_2_CHARECTERTONUMBER_H
#define ALENOV_BSE204_AVS_2_CHARECTERTONUMBER_H
#include "text.h"
#include <fstream>

using std::to_string;

class charecterToNumber: public text{
public:

    void Encrypt() override{
        for (char i : message) {
            if (i == ' ') {
                encrypted += "/ ";
            } else {
                encrypted += to_string((int)i)+" ";
            }
        }
        Quotient();
        // Заполняем значение частного.
    }

    // Перепись вывода в файл родительского класса.
    void Out(ofstream &ofst) override{
        ofst << "Text: " << message
             << "\nEncryption by replacing characters with numbers: " << encrypted << "\n";
    }
};

#endif //ALENOV_BSE204_AVS_2_CHARECTERTONUMBER_H
