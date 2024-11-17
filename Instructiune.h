//
// Created by Admin on 08.11.2024.
//

#ifndef INSTRUCTIUNE_H
#define INSTRUCTIUNE_H
#include <iostream>
#include "Instructiune.h"

using namespace std;

class Instructiune {
public:
    int id;
    int reteta_id;
    int pas;
    string descriere;

    // Constructor
    Instructiune(int id, int reteta_id, int pas, const string& descriere)
            : id(id), reteta_id(reteta_id), pas(pas), descriere(descriere) {}
};



#endif //INSTRUCTIUNE_H
