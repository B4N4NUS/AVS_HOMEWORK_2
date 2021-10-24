//------------------------------------------------------------------------------
// container.h - содержит класс простейшего контейнера.
//------------------------------------------------------------------------------

#ifndef ALENOV_BSE204_AVS_2_CONTAINER_H
#define ALENOV_BSE204_AVS_2_CONTAINER_H

#include "text.h"
#include "cyclicShift.h"
#include "charecterReplacement.h"
#include "charecterToNumber.h"
#include <iostream>

using std::cout;

// Структура textTuple нужна для реализации straight merge.
struct textTuple {
public:
    int index;
    double quotient;
};


class container {
public:
    enum {
        max_len = 10000
    }; // максимальная длина
    int len; // текущая длина
    text *cont[max_len];

//------------------------------------------------------------------------------
// Инициализация контейнера.
    void Init() {
        len = 0;
        cout << "container was created\n";
    }

//------------------------------------------------------------------------------
// Очистка контейнера от элементов (освобождение памяти)
    void Clear() {
        for (int i = 0; i < len; i++) {
            delete cont[i];
        }
        len = 0;
        cout << "container was cleared\n";
    }

//------------------------------------------------------------------------------
// Ввод содержимого контейнера из указанного потока.
    void In(ifstream &ifst) {
        int key = 0;
        while (!ifst.eof()) {
            auto *ctn = new charecterToNumber;
            auto *cr = new charecterReplacement;
            auto *cs = new cyclicShift;

            ifst >> key;
            switch (key) {
                case 1:
                    cr->In(ifst);
                    cont[len++] = cr;
                    break;
                case 2:
                    cs->In(ifst);
                    cont[len++] = cs;
                    break;
                case 3:
                    ctn->In(ifst);
                    cont[len++] = ctn;
                    break;
                default:
                    cout << "An Error Occured";
                    return;
            }
        }
        cout << "reading was finished\n";
        cout << "container was filled\n";
    }

//------------------------------------------------------------------------------
// Случайный ввод содержимого контейнера.
    void InRnd(int size) {
        int key;
        while (len < size) {
            auto *ctn = new charecterToNumber;
            auto *cr = new charecterReplacement;
            auto *cs = new cyclicShift;

            key = rand() % 3 + 1;

            switch (key) {
                case 1:
                    cr->InRnd();
                    cont[len++] = cr;
                    break;
                case 2:
                    cs->InRnd();
                    cont[len++] = cs;
                    break;
                case 3:
                    ctn->InRnd();
                    cont[len++] = ctn;
                    break;
                default:
                    cout << "An Error Occured";
                    return;
            }
        }
        cout << "container was filled randomly\n";
    }

//------------------------------------------------------------------------------
// Вывод содержимого контейнера в указанный поток.
    void Out(ofstream &ofst) {
        ofst << "Container contains " << len << " elements." << "\n";
        for (int i = 0; i < len; i++) {
            ofst << i << ": ";
            cont[i]->Out(ofst);
        }
        cout << "container was printed\n";
    }

//------------------------------------------------------------------------------
// Вывод содержимого контейнера в консоль (Для Debug'а).
    void Print() {
        for (int i = 0; i < len; i++) {
            cout << i << "\n" << cont[i]->message << "\n" << cont[i]->encrypted << "\n";
        }
    }

//--------------------------------------------------------------------------------
// Реализация функции прямого слияния (Straight Merge)
    void MergeSort(ofstream &ofst) {
        // Компилятор не дает мне адекватно сортировать массив ссылок на text,
        // Поэтому я создаю массив из "кортежа" значений quotient и index для
        // каждого элемента cont и сортирую его.
        textTuple quotAndInd[max_len];
        for (int i = 0; i < len; i++) {
            quotAndInd[i].index = i;
            quotAndInd[i].quotient = cont[i]->quotient;
        }

        // Переменные для сортировки.
        size_t blockSizeIterator, blockIterator,leftBlockIterator,rightBlockIterator,mergeIterator,leftBorder,midBorder,rightBorder;

        // Сама сортировка.
        for (blockSizeIterator = 1; blockSizeIterator < len; blockSizeIterator *= 2) {
            for (blockIterator = 0; blockIterator < len -blockSizeIterator; blockIterator += 2 * blockSizeIterator) {
                // Производим слияние с сортировкой пары блоков начинающуюся с элемента BlockIterator.
                // Левый размером BlockSizeIterator, правый размером BlockSizeIterator или меньше.
                leftBlockIterator = 0;
                rightBlockIterator = 0;
                leftBorder = blockIterator;
                midBorder = blockIterator + blockSizeIterator;
                rightBorder = blockIterator + 2 * blockSizeIterator;
                rightBorder = (rightBorder < len) ? rightBorder : len;
                auto *SortedBlock = new textTuple[rightBorder - leftBorder];

                // Пока в обоих массивах есть элементы выбираем меньший из них и заносим в отсортированный блок.
                while (leftBorder + leftBlockIterator < midBorder && midBorder + rightBlockIterator < rightBorder) {
                    if (quotAndInd[leftBorder + leftBlockIterator].quotient <
                        quotAndInd[midBorder + rightBlockIterator].quotient) {
                        SortedBlock[leftBlockIterator + rightBlockIterator] = quotAndInd[leftBorder +
                                                                                         leftBlockIterator];
                        leftBlockIterator += 1;
                    } else {
                        SortedBlock[leftBlockIterator + rightBlockIterator] = quotAndInd[midBorder +
                                                                                         rightBlockIterator];
                        rightBlockIterator += 1;
                    }
                }
                // После этого заносим оставшиеся элементы из левого или правого блока.
                while (leftBorder + leftBlockIterator < midBorder) {
                    SortedBlock[leftBlockIterator + rightBlockIterator] = quotAndInd[leftBorder + leftBlockIterator];
                    leftBlockIterator += 1;
                }
                while (midBorder + rightBlockIterator < rightBorder) {
                    SortedBlock[leftBlockIterator + rightBlockIterator] = quotAndInd[midBorder + rightBlockIterator];
                    rightBlockIterator += 1;
                }

                for (mergeIterator = 0; mergeIterator < leftBlockIterator + rightBlockIterator; mergeIterator++) {
                    quotAndInd[leftBorder + mergeIterator] = SortedBlock[mergeIterator];
                }
                delete[] SortedBlock;
            }
        }

        // Сортируем cont через отсортированный массив кортежей.
        text *tmp[max_len];
        for (int i = 0; i < len; i++) {
            tmp[i] = cont[i];
        }
        for (int i = 0; i < len; i++) {
            cont[i] = tmp[quotAndInd[i].index];
        }


        // Выводим все в файл.
        ofst << "Container was sorted by straight merge and contains " << len << " elements.\n";
        for (int i = 0; i < len; i++) {
            ofst << i << ": Quotient = " << cont[i]->quotient << ": ";
            cont[i]->Out(ofst);
        }
        cout << "container was mergesorted\n";
    }
};

#endif //ALENOV_BSE204_AVS_2_CONTAINER_H
