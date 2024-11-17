//
// Created by Admin on 08.11.2024.
//

#ifndef RETETA_H
#define RETETA_H
#include <iostream>
#include "Ingredient.h"
#include "Instructiune.h"

using namespace std;
class Reteta {
public:
    int id;
    string nume;
    string descriere;
    int durata_preparare;
    int portii;
    string categorie;
    string tip_dieta;

    vector<Ingredient> ingrediente;
    vector<Instructiune> instructiuni;
    // Constructor
    Reteta() = default;
    Reteta(int id, const std::string& nume, const std::string& descriere, int durata_preparare,
           int portii, const std::string& categorie, const std::string& tip_dieta)
        : id(id), nume(nume), descriere(descriere), durata_preparare(durata_preparare),
          portii(portii), categorie(categorie), tip_dieta(tip_dieta) {}
};


#endif //RETETA_H
