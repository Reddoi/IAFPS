//
// Created by Admin on 09.11.2024.
//

#ifndef FUNCTIIBAZADEDATE_H
#define FUNCTIIBAZADEDATE_H

#include <iostream>
#include <vector>
#include <sqlite3.h>
#include "Reteta.h"
#include <string>
#include <map>
#include <svm.h>
using namespace std;

sqlite3* openDatabase(const string& ingrediente);
vector<Reteta> readRecipes(sqlite3* db);
Reteta getRecipeByName(sqlite3* db, const string& numeReteta);
vector<Reteta> filterRecipesByCategory(sqlite3* db, const string& categorie);
vector<Reteta> filterRecipesByDiet(sqlite3* db, const string& tip_dieta);
vector<Reteta> sortRecipesByName(vector<Reteta>& retete);
vector<Reteta> sortRecipesByPreparationTime(vector<Reteta>& retete);
vector<tuple<string, double, string>> getIngredientsForRecipe(sqlite3* db, int reteta_id);
string getIngredientNamyById(sqlite3* db, int ingredient_id);
vector<Ingredient> readAllIngredients(sqlite3* db);
vector<Instructiune> getPreparationStepsForRecipe(sqlite3* db, int reteta_id);
Reteta getRecipeById(sqlite3* db, int id);
map<string, double> calculateNutritionalValue(sqlite3* db, int reteta_id);
double getConverstionFactor(sqlite3* db, const string& unitate);
string removeDiacritics(const string& input);
struct UserPreferences {
    vector<string> availableIngredients;
    string dietaryPreference;
};
double calculateSimilarity(const vector<string>& recipeIngredients, const vector<string>& userPreferences);
vector<Reteta> recommendRecipesContentBased(sqlite3* db, const UserPreferences& preferences);

#endif //FUNCTIIBAZADEDATE_H
