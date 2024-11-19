// DecisionTreeClassifier.cpp
#include "functiiBazaDeDate.h"
#include "DecisionTreeClassifier.h"

using namespace std;
using namespace mlpack;


arma::mat prepareData(sqlite3* db, arma::Row<size_t>& labels) {
    vector<Reteta> retete = readRecipes(db);
    arma::mat data(4, retete.size()); // 4 features: energie_kcal, proteine, carbohidrati, durata_preparare
    labels.set_size(retete.size());

    for (size_t i = 0; i < retete.size(); ++i) {
        map<string, double> nutritionalValues = calculateNutritionalValue(db, retete[i].id);
        data(0, i) = nutritionalValues["energie_kcal"];
        data(1, i) = nutritionalValues["proteine"];
        data(2, i) = nutritionalValues["carbohidrati"];
        data(3, i) = retete[i].durata_preparare;

        // Labeling based on nutritional values
        if (nutritionalValues["energie_kcal"] < 200) {
            labels[i] = 0; // Low Calorie
        } else if (nutritionalValues["carbohidrati"] < 20) {
            labels[i] = 1; // Low Carb
        } else {
            labels[i] = 2; // Other
        }
    }

    return data;
}

void trainDecisionTreeModel(sqlite3* db) {
    arma::Row<size_t> labels;
    arma::mat data = prepareData(db, labels);

    DecisionTree<> tree(data, labels, 3); // 3 classes: Low Calorie, Low Carb, Other

    // Save the model
    data::Save("decision_tree_model.xml", "tree", tree);
}

void classifyRecipe(sqlite3* db, int recipeId) {
    // Load the model
    DecisionTree<> tree;
    data::Load("decision_tree_model.xml", "tree", tree);

    // Prepare the data for the given recipe
    map<string, double> nutritionalValues = calculateNutritionalValue(db, recipeId);
    arma::rowvec sample(4);
    sample(0) = nutritionalValues["energie_kcal"];
    sample(1) = nutritionalValues["proteine"];
    sample(2) = nutritionalValues["carbohidrati"];
    sample(3) = getRecipeById(db, recipeId).durata_preparare;

    // Classify the recipe
    size_t prediction = tree.Classify(sample);

    // Output the classification result
    switch (prediction) {
        case 0:
            cout << "Recipe is classified as Low Calorie" << endl;
            break;
        case 1:
            cout << "Recipe is classified as Low Carb" << endl;
            break;
        default:
            cout << "Recipe is classified as Other" << endl;
            break;
    }
}