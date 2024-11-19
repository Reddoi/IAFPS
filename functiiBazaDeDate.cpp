#include "functiiBazaDeDate.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <locale>
#include <codecvt>
#include <cmath>
#include <unordered_set>

using namespace std;

sqlite3* openDatabase(const string& ingrediente) {
    sqlite3* db;
    if(sqlite3_open("D:/UTM/IAFPS Proiect/ingrediente.db", &db)) {
        cerr << "Nu s-a putut deschide baza de date" << sqlite3_errmsg(db) << endl;
        return nullptr;
    }
    return db;
}

vector<Reteta> readRecipes(sqlite3* db) {
    vector<Reteta> retete;
    string sql = "SELECT id, nume, descriere, durata_preparare, portii, categorie, tip_dieta FROM retete";
    sqlite3_stmt * stmt;

    if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Eroare la pregatirea interogarii" << sqlite3_errmsg(db) << endl;
        return retete;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id =sqlite3_column_int(stmt, 0);
        string nume = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string descriere = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        int durata_preparare = sqlite3_column_int(stmt, 3);
        int portii = sqlite3_column_int(stmt, 4);
        string categorie = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        string tip_dieta = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        retete.emplace_back(id, nume, descriere, durata_preparare, portii, categorie, tip_dieta);
    }
    sqlite3_finalize(stmt);
    return retete;
}
Reteta getRecipeByName(sqlite3* db, const string& numeReteta) {
    Reteta reteta;
    string sql = "SELECT id, nume, descriere, durata_preparare, portii, categorie, tip_dieta FROM retete WHERE nume LIKE ? COLLATE NOCASE";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Eroare la pregatirea interogarii" << sqlite3_errmsg(db) << endl;
        return reteta;
    }
    string searchPattern = "%" + numeReteta + "%";
    sqlite3_bind_text(stmt, 1, searchPattern.c_str(), -1, SQLITE_STATIC);

    if(sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string nume = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string descriere = (sqlite3_column_type(stmt, 2) !=SQLITE_NULL) ?
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)) : "";
        int durata_preparare = (sqlite3_column_int(stmt, 3) != SQLITE_NULL) ? sqlite3_column_int(stmt,3) : 0;
        int portii = (sqlite3_column_int(stmt, 4) != SQLITE_NULL) ? sqlite3_column_int(stmt, 4) : 0;
        string categorie = (sqlite3_column_type(stmt, 5) != SQLITE_NULL) ?
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)) : "";
        string tip_dieta = (sqlite3_column_type(stmt, 6) != SQLITE_NULL) ?
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)) : "";
        reteta = Reteta(id, nume, descriere, durata_preparare, portii, categorie, tip_dieta);
    } else {
        cout << "Nicio reteta gasita cu numele: " << numeReteta << endl;
    }
    sqlite3_finalize(stmt);
    return reteta;
}

vector<Reteta> filterRecipesByCategory(sqlite3 *db, const string& categorie) {
    vector<Reteta> retete;
    string sql = "SELECT id, nume, descriere, durata_preparare, portii, categorie, tip_dieta FROM retete WHERE categorie = ?";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Eroare la pregatirea interogarii" << sqlite3_errmsg(db) << endl;
        return retete;
    }
    sqlite3_bind_text(stmt, 1, categorie.c_str(), -1, SQLITE_STATIC);

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string nume = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string descriere = (sqlite3_column_type(stmt, 2) != SQLITE_NULL) ?
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)) : "";
        int durata_preparare = (sqlite3_column_int(stmt, 3) != SQLITE_NULL) ? sqlite3_column_int(stmt, 3) : 0;
        int portii = (sqlite3_column_int(stmt, 4) != SQLITE_NULL) ? sqlite3_column_int(stmt, 4) : 0;
        string categorie = (sqlite3_column_type(stmt, 5) != SQLITE_NULL) ?
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)) : "";
        string tip_dieta = (sqlite3_column_type(stmt, 6) != SQLITE_NULL) ?
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)) : "";
        retete.emplace_back(id, nume, descriere, durata_preparare, portii, categorie, tip_dieta);
    }
    sqlite3_finalize(stmt);
    return retete;
}

vector<Reteta> filterRecipesByDiet(sqlite3 *db, const string &tip_dieta) {
    vector<Reteta> retete;
    string sql = "SELECT id, nume, descriere, durata_preparare, portii, categorie, tip_dieta FROM retete WHERE tip_dieta = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Eroare la pregatirea interogarii" << sqlite3_errmsg(db) << endl;
        return retete;
    }
    sqlite3_bind_text(stmt, 1, tip_dieta.c_str(), -1, SQLITE_STATIC);

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string nume = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string descriere = (sqlite3_column_type(stmt, 2) != SQLITE_NULL) ?
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)) : "";
        int durata_preparare = (sqlite3_column_int(stmt, 3) != SQLITE_NULL) ? sqlite3_column_int(stmt, 3) : 0;
        int portii = (sqlite3_column_int(stmt, 4) != SQLITE_NULL) ? sqlite3_column_int(stmt, 4) : 0;
        string categorie = (sqlite3_column_type(stmt, 5) != SQLITE_NULL) ?
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)) : "";
        string tip_dieta = (sqlite3_column_type(stmt, 6) != SQLITE_NULL) ?
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)) : "";
        retete.emplace_back(id, nume, descriere, durata_preparare, portii, categorie, tip_dieta);
    }
    sqlite3_finalize(stmt);
    return retete;
}

vector<Reteta> sortRecipesByName(vector<Reteta> &retete) {
    sort(retete.begin(), retete.end(), [](const Reteta& a, const Reteta& b) {
        return a.nume < b.nume;
    });
    return retete;
}
vector<Reteta> sortRecipesByPreparationTime(vector<Reteta> &retete) {
    sort(retete.begin(), retete.end(), [](const Reteta& a, const Reteta& b) {
        return a.durata_preparare < b.durata_preparare;
    });
    return retete;
}

vector<tuple<string, double, string>> getIngredientsForRecipe(sqlite3* db, int reteta_id) {
    vector<tuple<string, double, string>> ingrediente;
    string sql = "SELECT ingredient_id, cantitate, unitate_masura FROM retete_ingrediente WHERE reteta_id = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Eroare la pregatirea interogarii" << sqlite3_errmsg(db) << endl;
        return ingrediente;
    }
    sqlite3_bind_int(stmt, 1, reteta_id);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int ingredient_id = sqlite3_column_int(stmt, 0);
        double cantitate = sqlite3_column_double(stmt, 1);
        string unitate_masura = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

        string nume_ingredient =  getIngredientNamyById(db, ingredient_id);

        ingrediente.emplace_back(nume_ingredient, cantitate, unitate_masura);
    }

    sqlite3_finalize(stmt);
    return ingrediente;
}

string getIngredientNamyById(sqlite3 *db, int ingredient_id) {
    string nume_ingredient;
    string sql = "SELECT nume FROM ingrediente WHERE id = ?";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Eroare la pregatirea interogarii" << sqlite3_errmsg(db) << endl;
        return nume_ingredient;
    }
    sqlite3_bind_int(stmt, 1, ingredient_id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        nume_ingredient = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }

    sqlite3_finalize(stmt);
    return nume_ingredient;
}

vector<Ingredient> readAllIngredients(sqlite3* db) {
    vector<Ingredient> ingrediente;
    string sql = "SELECT id, nume, categorie, energie_kj, energie_kcal, proteine, grasimi_totale, grasimi_saturate, grasimi_nesaturate, carbohidrati, zahar, vitamine FROM ingrediente";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Eroare la pregatirea interogarii" << sqlite3_errmsg(db) << endl;
        return ingrediente;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string nume = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string categorie = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        int energie_kj = sqlite3_column_int(stmt, 3);
        int energie_kcal = sqlite3_column_int(stmt, 4);
        float proteine = static_cast<float>(sqlite3_column_double(stmt, 5));
        float grasimi_totale = static_cast<float>(sqlite3_column_double(stmt, 6));
        float grasimi_saturate = static_cast<float>(sqlite3_column_double(stmt, 7));
        float grasimi_nesaturate = static_cast<float>(sqlite3_column_double(stmt, 8));
        float carbohidrati = static_cast<float>(sqlite3_column_double(stmt, 9));
        float zahar = static_cast<float>(sqlite3_column_double(stmt, 10));
        string vitamine = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 11));

        ingrediente.emplace_back(id, nume, categorie, energie_kj, energie_kcal, proteine, grasimi_totale, grasimi_saturate, grasimi_nesaturate, carbohidrati, zahar, vitamine);
    }
    sqlite3_finalize(stmt);
    return ingrediente;
    }

    vector<Instructiune> getPreparationStepsForRecipe(sqlite3* db, int reteta_id) {
    vector<Instructiune> instructiuni;
    string sql = "SELECT id, reteta_id, pas, descriere FROM instructiuni_retete WHERE reteta_id = ? ORDER BY pas";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Eroare la pregatirea interogarii" << sqlite3_errmsg(db) << endl;
        return instructiuni;
    }
    sqlite3_bind_int(stmt, 1, reteta_id);

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        int reteta_id = sqlite3_column_int(stmt, 1);
        int pas = sqlite3_column_int(stmt, 2);
        string descriere = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

        instructiuni.emplace_back(id, reteta_id, pas, descriere);
    }
    sqlite3_finalize(stmt);
    return instructiuni;
}

Reteta getRecipeById(sqlite3* db, int id) {
    Reteta reteta;
    string sql = "SELECT id, nume, descriere, durata_preparare, portii, categorie, tip_dieta FROM retete WHERE id = ?";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Eroare la pregatirea interogarii" << sqlite3_errmsg(db) << endl;
        return reteta;
    }
    sqlite3_bind_int(stmt, 1, id);

    if(sqlite3_step(stmt) == SQLITE_ROW) {
        reteta.id = sqlite3_column_int(stmt, 0);
        reteta.nume = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        reteta.descriere = (sqlite3_column_type(stmt, 2) != SQLITE_NULL) ?
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)) : "";
        reteta.durata_preparare = (sqlite3_column_int(stmt, 3) != SQLITE_NULL) ? sqlite3_column_int(stmt, 3) : 0;
        reteta.portii = (sqlite3_column_int(stmt, 4) != SQLITE_NULL) ? sqlite3_column_int(stmt, 4) : 0;
        reteta.categorie = (sqlite3_column_type(stmt, 5) != SQLITE_NULL) ?
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)) : "";
        reteta.tip_dieta = (sqlite3_column_type(stmt, 6) != SQLITE_NULL) ?
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)) : "";
    }
    sqlite3_finalize(stmt);
    return reteta;
}

double getConversionFactor(sqlite3* db, const string& unitate) {
    string sql = "SELECT factor_conversie FROM conversie_unitate WHERE unitate = ?";
    sqlite3_stmt* stmt;
    double factor = 1.0;  // Default value if unit not found

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Eroare la pregătirea interogării pentru factor de conversie: " << sqlite3_errmsg(db) << endl;
        return factor;
    }

    sqlite3_bind_text(stmt, 1, unitate.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        factor = sqlite3_column_double(stmt, 0);
    } else {
        cerr << "Unitate necunoscută: " << unitate << endl;
    }

    sqlite3_finalize(stmt);
    return factor;
}


map<string, double> calculateNutritionalValue(sqlite3* db, int reteta_id) {
    map<string, double> nutritionalValues = {
    {"energie_kj", 0.0},
    {"energie_kcal", 0.0},
    {"proteine", 0.0},
    {"grasimi_totale", 0.0},
    {"grasimi_saturate", 0.0},
    {"grasimi_nesaturate", 0.0},
    {"carbohidrati", 0.0},
    {"zahar", 0.0},
    };
    string sql = "SELECT i.energie_kj, i.energie_kcal, i.proteine, i.grasimi_totale, "
                 "i.grasimi_saturate, i.grasimi_nesaturate, i.carbohidrati, i.zahar, "
                 "ri.cantitate, ri.unitate_masura FROM ingrediente i "
                 "JOIN retete_ingrediente ri ON i.id = ri.ingredient_id WHERE ri.reteta_id = ?";
        sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Eroare la pregatirea interogarii" << sqlite3_errmsg(db) << endl;
        return nutritionalValues;
    }
    sqlite3_bind_int(stmt, 1, reteta_id);
    while(sqlite3_step(stmt) == SQLITE_ROW) {
        double cantitate = sqlite3_column_double(stmt, 8);
        string unitate_masura = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9));
        double factor_conversie = getConversionFactor(db, unitate_masura);
        double cantitateInGrame = cantitate * factor_conversie / 100.0;

        nutritionalValues["energie_kj"] += sqlite3_column_double(stmt, 0) * cantitateInGrame;
        nutritionalValues["energie_kcal"] += sqlite3_column_double(stmt, 1) * cantitateInGrame;
        nutritionalValues["proteine"] += sqlite3_column_double(stmt, 2) * cantitateInGrame;
        nutritionalValues["grasimi_totale"] += sqlite3_column_double(stmt, 3) * cantitateInGrame;
        nutritionalValues["grasimi_saturate"] += sqlite3_column_double(stmt, 4) * cantitateInGrame;
        nutritionalValues["grasimi_nesaturate"] += sqlite3_column_double(stmt, 5) * cantitateInGrame;
        nutritionalValues["carbohidrati"] += sqlite3_column_double(stmt, 6) * cantitateInGrame;
        nutritionalValues["zahar"] += sqlite3_column_double(stmt, 7) * cantitateInGrame;
    }
    sqlite3_finalize(stmt);
    return nutritionalValues;
}

vector<Reteta> recommendRecipes(sqlite3* db, const UserPreferences& preferences) {
    vector<Reteta> allRecipes = readRecipes(db);
    vector<Reteta> filteredRecipes;

    vector<string> lowerCaseIngredients = preferences.availableIngredients;
    for(auto& ingredient : lowerCaseIngredients) {
        transform(ingredient.begin(), ingredient.end(), ingredient.begin(), ::tolower);
    }

    // filter recipes based on available ingredients
    for (const auto& recipe : allRecipes) {
        vector<tuple<string, double, string>> ingredients = getIngredientsForRecipe(db, recipe.id);
        bool hasAnyIngredient = false;
        for (const auto& ingredient : ingredients) {
            string ingredientName = get<0>(ingredient);
            transform(ingredientName.begin(), ingredientName.end(), ingredientName.begin(), ::tolower);
            if (find(lowerCaseIngredients.begin(), lowerCaseIngredients.end(),  ingredientName) != lowerCaseIngredients.end()) {
                hasAnyIngredient = true;
                break;
            }
        }
        if(hasAnyIngredient) {
            filteredRecipes.push_back(recipe);
        }
    }
    return filteredRecipes;
}

std::string removeDiacritics(const std::string& input) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(input);
    std::wstring result;
    for (wchar_t c : wide) {
        switch (c) {
            case L'ă': case L'â': case L'á': case L'à': case L'ä': case L'ã': case L'å': case L'ā': case L'ą': case L'ǎ': result += L'a'; break;
            case L'Ă': case L'Â': case L'Á': case L'À': case L'Ä': case L'Ã': case L'Å': case L'Ā': case L'Ą': case L'Ǎ': result += L'A'; break;
            case L'î': case L'í': case L'ì': case L'ï': case L'ĩ': case L'ī': case L'į': case L'ǐ': result += L'i'; break;
            case L'Î': case L'Í': case L'Ì': case L'Ï': case L'Ĩ': case L'Ī': case L'Į': case L'Ǐ': result += L'I'; break;
            case L'ș': case L'ş': result += L's'; break;
            case L'Ș': case L'Ş': result += L'S'; break;
            case L'ț': case L'ţ': result += L't'; break;
            case L'Ț': case L'Ţ': result += L'T'; break;
            case L'ó': case L'ò': case L'ö': case L'õ': case L'ō': case L'ő': case L'ǒ': result += L'o'; break;
            case L'Ó': case L'Ò': case L'Ö': case L'Õ': case L'Ō': case L'Ő': case L'Ǒ': result += L'O'; break;
            case L'ú': case L'ù': case L'ü': case L'ũ': case L'ū': case L'ű': case L'ǔ': result += L'u'; break;
            case L'Ú': case L'Ù': case L'Ü': case L'Ũ': case L'Ū': case L'Ű': case L'Ǔ': result += L'U'; break;
            case L'é': case L'è': case L'ë': case L'ẽ': case L'ē': case L'ę': case L'ě': result += L'e'; break;
            case L'É': case L'È': case L'Ë': case L'Ẽ': case L'Ē': case L'Ę': case L'Ě': result += L'E'; break;
            case L'ç': result += L'c'; break;
            case L'Ç': result += L'C'; break;
            case L'ñ': result += L'n'; break;
            case L'Ñ': result += L'N'; break;
            default: result += c; break;
        }
    }
    return converter.to_bytes(result);
}

double calculateSimilarity(const vector<string>& recipeIngredients, const vector<string>& userPreferences) {
    unordered_set<string> recipeSet(recipeIngredients.begin(), recipeIngredients.end());
    unordered_set<string> userSet(userPreferences.begin(), userPreferences.end());

    vector<string> intersection;
    for (const auto& ingredient : userSet) {
        if (recipeSet.find(ingredient) != recipeSet.end()) {
            intersection.push_back(ingredient);
        }
    }

    double similarity = static_cast<double>(intersection.size()) / sqrt(recipeSet.size() * userSet.size());
    return similarity;
}

vector<Reteta> recommendRecipesContentBased(sqlite3* db, const UserPreferences& preferences) {
    vector<Reteta> allRecipes = readRecipes(db);
    vector<Reteta> recommendedRecipes;

    for (const auto& recipe : allRecipes) {
        vector<tuple<string, double, string>> ingredients = getIngredientsForRecipe(db, recipe.id);
        vector<string> ingredientNames;
        for (const auto& ingredient : ingredients) {
            string ingredientName = get<0>(ingredient);
            string normalizedIngredientName = removeDiacritics(ingredientName);
            transform(normalizedIngredientName.begin(), normalizedIngredientName.end(), normalizedIngredientName.begin(), ::tolower);
            ingredientNames.push_back(normalizedIngredientName);
        }

        double similarity = calculateSimilarity(ingredientNames, preferences.availableIngredients);
        if (similarity > 0.0) {
            recommendedRecipes.push_back(recipe);
        }
    }

    sort(recommendedRecipes.begin(), recommendedRecipes.end(), [&](const Reteta& a, const Reteta& b) {
        vector<tuple<string, double, string>> ingredientsA = getIngredientsForRecipe(db, a.id);
        vector<string> ingredientNamesA;
        for (const auto& ingredient : ingredientsA) {
            string ingredientName = get<0>(ingredient);
            string normalizedIngredientName = removeDiacritics(ingredientName);
            transform(normalizedIngredientName.begin(), normalizedIngredientName.end(), normalizedIngredientName.begin(), ::tolower);
             ingredientNamesA.push_back(normalizedIngredientName);
        }

        vector<tuple<string, double, string>> ingredientsB = getIngredientsForRecipe(db, b.id);
        vector<string> ingredientNamesB;
        for (const auto& ingredient : ingredientsB) {
            string ingredientName = get<0>(ingredient);
            string normalizedIngredientName = removeDiacritics(ingredientName);
            transform(normalizedIngredientName.begin(), normalizedIngredientName.end(), normalizedIngredientName.begin(), ::tolower);
            ingredientNamesB.push_back(normalizedIngredientName);
        }

        return calculateSimilarity(ingredientNamesA, preferences.availableIngredients) >
               calculateSimilarity(ingredientNamesB, preferences.availableIngredients);
    });

    return recommendedRecipes;
}