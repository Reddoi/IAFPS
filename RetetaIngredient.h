
#ifndef RETETAINGREDIENT_H
#define RETETAINGREDIENT_H
#include <bits/stdc++.h>
 using namespace std;

class RetetaIngredient {
public:
    int id;
    int reteta_id;
    int ingredient_id;
    double cantitate;
    string unitate_masura;

    RetetaIngredient(int id, int reteta_id, int ingredient_id, double cantitate, const string& unitate_masura)
        : id(id), reteta_id(reteta_id), ingredient_id(ingredient_id), cantitate(cantitate), unitate_masura(unitate_masura) {}
};

#endif //RETETAINGREDIENT_H
