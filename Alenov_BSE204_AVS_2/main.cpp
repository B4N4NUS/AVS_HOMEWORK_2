//------------------------------------------------------------------------------
// main.cpp - содержит главную функцию,
// обеспечивающую простое тестирование.
//------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include "cyclicShift.h"
#include "charecterReplacement.h"
#include "charecterToNumber.h"
#include "container.h"
//#include "chrono"
using std::string;
using std::getline;
using std::cout;
using std::cin;
//using namespace std::chrono;

//------------------------------------------------------------------------------
// Выводит сообщение о некорректном вводе.
void errMessage1() {
    cout << "incorrect command line!\n"
                "  Waited:\n"
                "     command -f infile outfile01 outfile02\n"
                "  Or:\n"
                "     command -r number outfile01 outfile02\n";
}

//------------------------------------------------------------------------------
// Выводит сообщение о некорректном вводе метода заполнения.
void errMessage2() {
    cout << "incorrect qualifier value!\n"
                "  Waited:\n"
                "     command -f infile outfile01 outfile02\n"
                "  Or:\n"
                "     command -r number outfile01 outfile02\n";
}
//------------------------------------------------------------------------------
// Точка входа.
int main(int argc, char *argv[]) {
    // Старт таймера.
    //auto start = high_resolution_clock::now();

    if (argc != 5) {
        errMessage1();
        return 1;
    }

    cout << "Start\n";
    container c{};
    c.Init();

    if (!strcmp(argv[1], "-f")) {
        ifstream ifst(argv[2]);
        if (ifst){
            c.In(ifst);
        } else {
            cout << "Incorrect path or file";
        }

    } else if (!strcmp(argv[1], "-r")) {
        auto size = std::stoi(argv[2]);
        if ((size < 1) || (size > 10000)) {
            cout << "incorrect number of words = " << size <<". Set 0 < number <= 10000\n";
            return 3;
        }
        // системные часы в качестве инициализатора.
        srand(static_cast<unsigned int>(time(0)));
        // Заполнение контейнера генератором случайных чисел.
        c.InRnd(size);
    } else {
        errMessage2();
        return 2;
    }

    // Вывод содержимого контейнера в файл.
    ofstream ofst1(argv[3]);
    ofst1 << "Filled container:\n";
    c.Out(ofst1);

    // Вторая часть задания (функция)
    ofstream ofst2(argv[4]);
    c.MergeSort(ofst2);

    c.Clear();
    cout << "Stop\n";

    // Конец таймера и вывод времени работы в консоль.

    //auto stop = high_resolution_clock::now();
    //auto duration = duration_cast<microseconds>(stop - start);
    //printf("%s","EXECUTION TIME - ");
    //printf("%d",duration.count());
    //printf("%s"," microseconds\n");
    //string await;
    //cin >> await;
    return 0;
}