//------------------------------------------------------------------------------------
// text.h - содержит родительский класс text.
//------------------------------------------------------------------------------------

#ifndef ALENOV_BSE204_AVS_2_TEXT_H
#define ALENOV_BSE204_AVS_2_TEXT_H

#include <string>
#include <fstream>
#include "rnd.h"

using std::ifstream;
using std::ofstream;

class text {
public:
    text()= default;

    string message;
    string encrypted;
    double quotient{};

//------------------------------------------------------------------------------
// Виртуальная заглушка для кодирования.
    virtual void Encrypt(){
        encrypted = message;
        std::cout << "text\n" << message <<"\n" << encrypted << "\n";
    }
//------------------------------------------------------------------------------
// Виртуальная заглушка для метода ввода.
    virtual void In(ifstream &ifst){
        string input;
        while(ifst >> input){
            if (input == ";"){
                break;
            }
            message += input +" ";
        }
        Encrypt();
    }
//------------------------------------------------------------------------------
// Виртуальная заглушка для метода рандомного заполнения.
    virtual void InRnd(){
        message = Random();
        Encrypt();
    }
//------------------------------------------------------------------------------
// Виртуальная заглушка для метода вывода.
    virtual void Out(ofstream &ofst){
        ofst << "SOMETHING WENT WRONG\n";
    }

//------------------------------------------------------------------------------
// Вычисление частного суммы кодов незашифрованной строки и ее длины.
    void Quotient(){
        int64_t sum = 0;
        for(char i : message){
            sum += i;
        }
        quotient = sum*1.0/message.size();
    }
};

#endif //ALENOV_BSE204_AVS_2_TEXT_H
