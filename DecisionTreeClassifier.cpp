// DecisionTreeClassifier.cpp
#define _HAS_STD_BYTE 0
#include "functiiBazaDeDate.h"
#include "DecisionTreeClassifier.h"
#include <wx/string.h>
#include <wx/msgdlg.h>

using namespace std;
using namespace mlpack;

arma::mat prepareData(sqlite3* db, arma::Row<size_t>& labels) {
    vector<Reteta> retete = readRecipes(db);
    arma::mat data(8, retete.size()); // 8 features: energie_kcal, proteine, carbohidrati, durata_preparare
    labels.set_size(retete.size());

    for (size_t i = 0; i < retete.size(); ++i) {
        map<string, double> nutritionalValues = calculateNutritionalValue(db, retete[i].id);
        data(0, i) = nutritionalValues["energie_kj"];
        data(1, i) = nutritionalValues["energie_kcal"];
        data(2, i) = nutritionalValues["proteine"];
        data(3, i) = nutritionalValues["grasimi_totale"];
        data(4, i) = nutritionalValues["grasimi_saturate"];
        data(5, i) = nutritionalValues["grasimi_nesaturate"];
        data(6, i) = nutritionalValues["carbohidrati"];
        data(7, i) = nutritionalValues["zahar"];

        // Labeling based on nutritional values
        if (nutritionalValues["grasimi_totale"] < 10.0) {
            labels[i] = 0; // Low Fat
        } else if (nutritionalValues["energie_kcal"] < 350.0) {
            labels[i] = 1; // Low Calorie
        } else if (nutritionalValues["carbohidrati"] < 20.0 && nutritionalValues["grasimi_totale"] > 10.0 && nutritionalValues["proteine"] > 5.0) {
            labels[i] = 2; // Keto
        } else if (nutritionalValues["carbohidrati"] < 50.0) {
            labels[i] = 3; // Low Carbs
        } else {
            labels[i] = 4; // Other
        }
    }
    return data;
}

void trainDecisionTreeModel(sqlite3* db) {
    arma::Row<size_t> labels;
    arma::mat data = prepareData(db, labels);

    DecisionTree<> tree(data, labels, 5); // 3 classes: Low Calorie, Low Carb, Keto, Low Fat, Other

    // Save the model
    data::Save("decision_tree_model.xml", "tree", tree);
}

void classifyRecipe(sqlite3* db, int recipeId) {
    // Load the model
    DecisionTree<> tree;
    data::Load("decision_tree_model.xml", "tree", tree);

    // Prepare the data for the given recipe
    map<string, double> nutritionalValues = calculateNutritionalValue(db, recipeId);
    arma::rowvec sample(8);
    sample(0) = nutritionalValues["energie_kj"];
    sample(1) = nutritionalValues["energie_kcal"];
    sample(2) = nutritionalValues["proteine"];
    sample(3) = nutritionalValues["grasimi_totale"];
    sample(4) = nutritionalValues["grasimi_saturate"];
    sample(5) = nutritionalValues["grasimi_nesaturate"];
    sample(6) = nutritionalValues["carbohidrati"];
    sample(7) = nutritionalValues["zahar"];

    // Classify the recipe
    size_t prediction = tree.Classify(sample);

    vector<wxString> classifications;
    switch(prediction) {
            case 0:
            classifications.push_back("Low Fat");
            break;
        case 1:
            classifications.push_back("Low Calorie");
            break;
        case 2:
            classifications.push_back("Keto");
            break;
        case 3:
            classifications.push_back("Low Carbs");
            break;
        default:
            classifications.push_back("Other");
            break;
    }

     if (nutritionalValues["grasimi_totale"] < 10.0) {
        classifications.push_back("Low Fat");
    }
    if (nutritionalValues["energie_kcal"] < 350.0) {
        classifications.push_back("Low Calorie");
    }
    if (nutritionalValues["carbohidrati"] < 20.0 && nutritionalValues["grasimi_totale"] > 10.0 && nutritionalValues["proteine"] > 5.0) {
        classifications.push_back("Keto");
    }
    if (nutritionalValues["carbohidrati"] < 50.0) {
        classifications.push_back("Low Carbs");
    }
    if (classifications.empty()) {
        classifications.push_back("Other");
    }

    sort(classifications.begin(), classifications.end());
    classifications.erase(unique(classifications.begin(), classifications.end()), classifications.end());

    wxArrayString classificationArray;
    for(const auto& classification : classifications) {
        classificationArray.Add(classification);
    }
     wxString classificationResult = wxJoin(classificationArray,',');

    wxMessageBox("Recipe is classified as: " + classificationResult, "Classification Result", wxOK | wxICON_INFORMATION);
}