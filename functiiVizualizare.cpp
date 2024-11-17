#include "functiiVizualizare.h"
#include <iostream>

using namespace std;

void showRecipes(const vector<Reteta>& retete) {
    for (const auto& reteta : retete) {
        cout << "ID: " << reteta.id << "\nNume: " << reteta.nume << "\nDescriere: " << reteta.descriere << "\nDurata preparare: "
        << reteta.durata_preparare << "\nPortii: " << reteta.portii << "\nCategorie: "
        << reteta.categorie << "\nTip dieta: " << reteta.tip_dieta << endl;
    }
}

void showRecipe(const Reteta& reteta) {
    cout << "ID: " << reteta.id << "\nNume: " << reteta.nume << "\nDescriere: " << reteta.descriere << "\nDurata preparare: "
         << reteta.durata_preparare << "\nPortii: " << reteta.portii << "\nCategorie: "
         << reteta.categorie << "\nTip dieta: " << reteta.tip_dieta << endl;
}
