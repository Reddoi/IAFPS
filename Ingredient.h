//
// Created by Admin on 08.11.2024.
//

#ifndef INGREDIENT_H
#define INGREDIENT_H
#include <iostream>
using namespace std;

class Ingredient {
public:
    int id;
    string nume;
    string categorie;
    int energie_kj;
    int energie_kcal;
    float proteine;
    float grasimi_totale;
    float grasimi_saturate;
    float grasimi_nesaturate;
    float carbohidrati;
    float zahar;
    string vitamine;

    // Constructor
    Ingredient(int id, const string& nume, const string& categorie, int energie_kj, int energie_kcal,
        float proteine, float grasimi_totale, float grasimi_saturate, float grasimi_nesaturate, float carbohidrati, float zahar, const string& vitamine)
            : id(id), nume(nume), categorie(categorie), energie_kj(energie_kj), energie_kcal(energie_kcal), proteine(proteine), grasimi_totale(grasimi_totale),
              grasimi_saturate(grasimi_saturate), grasimi_nesaturate(grasimi_nesaturate), carbohidrati(carbohidrati), zahar(zahar), vitamine(vitamine) {}
};


#endif //INGREDIENT_H
