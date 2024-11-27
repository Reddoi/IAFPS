#include "MainFrame.h"
#include "functiiBazaDeDate.h"
#include "functiiVizualizare.h"
#include <wx/tokenzr.h>
#include <string>
#include "DecisionTreeClassifier.h"


wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(wxID_EXIT, MainFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
    EVT_MENU(ID_ShowRecipes, MainFrame::OnShowRecipes)
    EVT_MENU(ID_SearchRecipe, MainFrame::OnSearchRecipe)
    EVT_MENU(ID_FilterByCategory, MainFrame::OnFilterByCategory)
    EVT_MENU(ID_FilterByDiet, MainFrame::OnFilterByDiet)
    EVT_MENU(ID_SortByName, MainFrame::OnSortByName)
    EVT_MENU(ID_SortByPreparationTime, MainFrame::OnSortByPreparationTime)
    EVT_MENU(ID_ShowAllIngredients, MainFrame::OnShowAllIngredients)
    EVT_MENU(ID_ShowRecipeDetails, MainFrame::OnShowRecipeDetails)
    EVT_MENU(ID_RecommendedRecipes, MainFrame::OnRecommendRecipes)
    EVT_BUTTON(ID_ClassifyRecipe, MainFrame::OnClassifyRecipe)
    EVT_MENU(ID_ClusterRecipes, MainFrame::OnClusterRecipes)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)) {
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");


    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Welcome to Recipe Manager!");


    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* contentSizer = new wxBoxSizer(wxVERTICAL);

    wxButton* showRecipesButton = new wxButton(this, ID_ShowRecipes, "Show Recipes");
    wxButton* searchRecipeButton = new wxButton(this, ID_SearchRecipe, "Search Recipe");
    wxButton* filterByCategoryButton = new wxButton(this, ID_FilterByCategory, "Filter by Category");
    wxButton* filterByDietButton = new wxButton(this, ID_FilterByDiet, "Filter by Diet");
    wxButton* sortByNameButton = new wxButton(this, ID_SortByName, "Sort by Name");
    wxButton* sortByPreparationTimeButton = new wxButton(this, ID_SortByPreparationTime, "Sort by Preparation Time");
    wxButton* showAllIngredientsButton = new wxButton(this, ID_ShowAllIngredients, "Show All Ingredients");
    wxButton* recommendRecipesButton = new wxButton(this, ID_RecommendedRecipes, "Recommended Recipes");
    wxButton* classifyRecipeButton = new wxButton(this, ID_ClassifyRecipe, "Classify Recipe");
    wxButton* clusterRecipesButton = new wxButton(this, ID_ClusterRecipes, "Cluster Recipes");

    showRecipesButton->Bind(wxEVT_BUTTON, &MainFrame::OnShowRecipes, this);
    searchRecipeButton->Bind(wxEVT_BUTTON, &MainFrame::OnSearchRecipe, this);
    filterByCategoryButton->Bind(wxEVT_BUTTON, &MainFrame::OnFilterByCategory, this);
    filterByDietButton->Bind(wxEVT_BUTTON, &MainFrame::OnFilterByDiet, this);
    sortByNameButton->Bind(wxEVT_BUTTON, &MainFrame::OnSortByName, this);
    sortByPreparationTimeButton->Bind(wxEVT_BUTTON, &MainFrame::OnSortByPreparationTime, this);
    showAllIngredientsButton->Bind(wxEVT_BUTTON, &MainFrame::OnShowAllIngredients, this);
    recommendRecipesButton->Bind(wxEVT_BUTTON, &MainFrame::OnRecommendRecipes, this);
    classifyRecipeButton->Bind(wxEVT_BUTTON, &MainFrame::OnClassifyRecipe, this);
    clusterRecipesButton->Bind(wxEVT_BUTTON, &MainFrame::OnClusterRecipes, this);


    buttonSizer->Add(showRecipesButton, 0, wxEXPAND | wxALL, 5);
    buttonSizer->Add(searchRecipeButton, 0, wxEXPAND | wxALL, 5);
    buttonSizer->Add(filterByCategoryButton, 0, wxEXPAND | wxALL, 5);
    buttonSizer->Add(filterByDietButton, 0, wxEXPAND | wxALL, 5);
    buttonSizer->Add(sortByNameButton, 0, wxEXPAND | wxALL, 5);
    buttonSizer->Add(sortByPreparationTimeButton, 0, wxEXPAND | wxALL, 5);
    buttonSizer->Add(showAllIngredientsButton, 0, wxEXPAND | wxALL, 5);
    buttonSizer->Add(recommendRecipesButton, 0, wxEXPAND | wxALL, 5);
    buttonSizer->Add(classifyRecipeButton, 0, wxEXPAND | wxALL, 5);
    buttonSizer->Add(clusterRecipesButton, 0, wxEXPAND | wxALL, 5);

    wxScrolledWindow* scrolledWindow = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
    scrolledWindow->SetScrollRate(5, 5);
    wxBoxSizer* scrolledSizer = new wxBoxSizer(wxVERTICAL);


    searchCtrl = new wxTextCtrl(scrolledWindow, wxID_ANY);
    searchButton = new wxButton(scrolledWindow, wxID_ANY, "Search ingredient");
    classifyButton = new wxButton(scrolledWindow, ID_ClassifyRecipe, "Classify Recipe");
    listBox = new wxListBox(scrolledWindow, wxID_ANY, wxDefaultPosition, wxSize(800, 400));


    scrolledSizer->Add(searchCtrl, 0, wxEXPAND | wxALL, 5);
    scrolledSizer->Add(searchButton, 0, wxEXPAND | wxALL, 5);
    scrolledSizer->Add(classifyButton, 0, wxEXPAND | wxALL, 5);
    scrolledSizer->Add(listBox, 1, wxEXPAND | wxALL, 10);

    scrolledWindow->SetSizer(scrolledSizer);

    mainSizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(scrolledWindow, 1, wxEXPAND | wxALL, 5);

    SetSizer(mainSizer);

    searchButton->Bind(wxEVT_BUTTON, &MainFrame::OnSearchIngredient, this);
    listBox->Bind(wxEVT_RIGHT_DOWN, &MainFrame::OnRightClick, this);

    ShowSearchControls(false, false);
}

void MainFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("This is a wxWidgets Recipe Manager application",
                 "About Recipe Manager", wxOK | wxICON_INFORMATION);
}

void MainFrame::ShowSearchControls(bool show, bool showClassifyButton) {
    searchCtrl->Show(show);
    searchButton->Show(show);
    classifyButton->Show(showClassifyButton);
    this->Layout();
}

void MainFrame::OnShowRecipes(wxCommandEvent& event) {
    // Implement the logic to show recipes
    sqlite3* db = openDatabase("ingrediente.db");
    if (!db) {
        wxMessageBox("Failed to open database", "Error", wxOK | wxICON_ERROR);
        return;
    }

    vector<Reteta> retete = readRecipes(db);
    listBox->Clear();
    for (const auto& reteta : retete) {
        listBox->Append(wxString::Format("ID: %d, Name: %s", reteta.id, reteta.nume));
    }

    sqlite3_close(db);
    ShowSearchControls(false, true);

}

void MainFrame::OnSearchIngredient(wxCommandEvent& event) {
    wxString searchTerm = searchCtrl->GetValue().Lower();
    string normalizedSearchTerm =removeDiacritics(string(searchTerm.mb_str()));

    sqlite3* db = openDatabase("ingrediente.db");
    if (!db) {
        wxMessageBox("Failed to open database", "Error", wxOK | wxICON_ERROR);
        return;
    }

    vector<Ingredient> ingrediente = readAllIngredients(db);
    listBox->Clear();
    for (const auto& ingredient : ingrediente) {
        wxString ingredientName = wxString::FromUTF8(ingredient.nume.c_str()).Lower();
        string normalizedIngredientName = removeDiacritics(string(ingredientName.mb_str()));
        if (normalizedIngredientName.find(normalizedSearchTerm) != string::npos) {
            listBox->Append(wxString::Format("ID: %d, Name: %s, Category: %s, Energy (kJ): %d, Energy (kcal): %d, "
                                             "Proteins: %.2f, Total Fats: %.2f, Saturated Fats: %.2f, Unsaturated Fats: %.2f, Carbohydrates: %.2f, "
                                             "Sugar: %.2f, Vitamins: %s",
                                             ingredient.id, ingredient.nume, ingredient.categorie, ingredient.energie_kj, ingredient.energie_kcal,
                                             ingredient.proteine, ingredient.grasimi_totale, ingredient.grasimi_saturate,
                                             ingredient.grasimi_nesaturate, ingredient.carbohidrati, ingredient.zahar, ingredient.vitamine));
        }
    }

    sqlite3_close(db);
}

void MainFrame::OnSearchRecipe(wxCommandEvent& event) {
    // Implement the logic to search for a recipe
    wxTextEntryDialog dialog(this, "Enter the name of the recipe", "Search Recipe");
    if(dialog.ShowModal() == wxID_OK) {
        wxString searchName = dialog.GetValue();
        sqlite3* db = openDatabase("ingrediente.db");
        if(!db) {
            wxMessageBox("Failed to open database", "Error", wxOK | wxICON_ERROR);
            return;
        }
            Reteta reteta = getRecipeByName(db, string(searchName.mb_str()));
            listBox -> Clear();
            if(reteta.id != 0) {
                listBox->Append(wxString::Format("ID: %d, Name: %s", reteta.id, reteta.nume));
            } else {
                listBox->Append("No recipe found with the given name");
            }
            sqlite3_close(db);
        }
    ShowSearchControls(false, true);
    }

void MainFrame::OnFilterByCategory(wxCommandEvent& event) {
    // Implement the logic to filter recipes by category
    wxTextEntryDialog dialog(this, "Enter the category to filter by: ", "Filter by Category");
    if(dialog.ShowModal() == wxID_OK) {
        wxString category = dialog.GetValue();
        sqlite3* db = openDatabase("ingrediente.db");
        if(!db) {
            wxMessageBox("Failed to open database", "Error", wxOK | wxICON_ERROR);
            return;
        }
        vector<Reteta> filteredRecipes = filterRecipesByCategory(db, string(category.mb_str()));
        listBox->Clear();
        for(const auto& reteta : filteredRecipes) {
            listBox->Append(wxString::Format("ID: %d, Name: %s", reteta.id, reteta.nume));
        }
        sqlite3_close(db);
    }
    ShowSearchControls(false, false);
}

void MainFrame::OnFilterByDiet(wxCommandEvent& event) {
    // Implement the logic to filter recipes by diet
    wxTextEntryDialog dialog(this, "Enter the diet to filter by: ", "Filter by Diet");
    if(dialog.ShowModal() == wxID_OK) {
        wxString dietType = dialog.GetValue();
        sqlite3* db = openDatabase("ingrediente.db");
        if(!db) {
            wxMessageBox("Failed to open database", "Error", wxOK | wxICON_ERROR);
            return;
        }
        vector<Reteta> filteredRecipes = filterRecipesByDiet(db, string(dietType.mb_str()));
        listBox->Clear();
        for(const auto& reteta : filteredRecipes) {
            listBox->Append(wxString::Format("ID: %d, Name: %s", reteta.id, reteta.nume));
        }
        sqlite3_close(db);
    }
    ShowSearchControls(false, false);
}

void MainFrame::OnSortByName(wxCommandEvent& event) {
    // Implement the logic to sort recipes by name
    sqlite3* db = openDatabase("ingrediente.db");
    if(!db) {
        wxMessageBox("Failed to open database", "Error", wxOK | wxICON_ERROR);
        return;
    }
    vector<Reteta> retete = readRecipes(db);
    retete = sortRecipesByName(retete);
    listBox->Clear();
    for(const auto& reteta : retete) {
        listBox->Append(wxString::Format("ID: %d, Name: %s", reteta.id, reteta.nume));
    }
    sqlite3_close(db);
    ShowSearchControls(false, false);
}

void MainFrame::OnSortByPreparationTime(wxCommandEvent& event) {
    // Implement the logic to sort recipes by preparation time
    sqlite3* db = openDatabase("ingrediente.db");
    if(!db) {
        wxMessageBox("Failed to open database", "Error", wxOK | wxICON_ERROR);
        return;
    }
    vector<Reteta> retete = readRecipes(db);
    retete = sortRecipesByPreparationTime(retete);
    listBox->Clear();
    for(const auto& reteta : retete) {
        listBox->Append(wxString::Format("ID: %d, Name: %s, Preparation Time: %d minute", reteta.id, reteta.nume, reteta.durata_preparare));
    }
    sqlite3_close(db);
    ShowSearchControls(false, false);
}


void MainFrame::OnShowAllIngredients(wxCommandEvent& event) {
    sqlite3* db = openDatabase("ingrediente.db");
    if(!db) {
        wxMessageBox("Failed to open database", "Error", wxOK | wxICON_ERROR);
        return;
    }
    vector<Ingredient> ingrediente = readAllIngredients(db);
    listBox->Clear();
    for(const auto& ingredient : ingrediente) {
        listBox->Append(wxString::Format("ID: %d, Name: %s, Category: %s, Energy (kJ): %d, Energy (kcal): %d, "
                                         "Proteins: %.2f, Total Fats: %.2f, Saturated Fats: %.2f, Unsaturated Fats: %.2f, Carbohydrates: %.2f, "
                                         "Sugar: %.2f, Vitamins: %s",
            ingredient.id, ingredient.nume, ingredient.categorie, ingredient.energie_kj, ingredient.energie_kcal,
            ingredient.proteine, ingredient.grasimi_totale, ingredient.grasimi_saturate,
            ingredient.grasimi_nesaturate, ingredient.carbohidrati, ingredient.zahar, ingredient.vitamine));
    }
    sqlite3_close(db);

    ShowSearchControls(true, false);
    if (!searchCtrl) {
        searchCtrl = new wxTextCtrl(this, wxID_ANY);
        searchButton = new wxButton(this, wxID_ANY, "Search ingredient");
        searchButton->Bind(wxEVT_BUTTON, &MainFrame::OnSearchIngredient, this);
        GetSizer()->Insert(0, searchCtrl, 0, wxEXPAND | wxALL, 5);
        GetSizer()->Insert(1, searchButton, 0, wxEXPAND | wxALL, 5);
        this->Layout();
    }
}

void MainFrame::OnRightClick(wxMouseEvent& event) {
    int selection = listBox->HitTest(event.GetPosition());
    if(selection != wxNOT_FOUND) {
        listBox->SetSelection(selection);
        wxMenu menu;
        menu.Append(ID_ShowRecipeDetails, "Show Recipe Details");
        PopupMenu(&menu, event.GetPosition());
    }
}
void MainFrame::OnShowRecipeDetails(wxCommandEvent& event) {
    int selection = listBox->GetSelection();
    if(selection == wxNOT_FOUND) {
        wxMessageBox("No recipe selected", "Error", wxOK | wxICON_ERROR);
        return;
    }
    wxString selectedRecipe = listBox -> GetString(selection);
    long recipeId;
    if(!selectedRecipe.BeforeFirst(',').AfterFirst(':').ToLong(&recipeId)) {
        wxMessageBox("Invalid recipe ID", "Error", wxOK | wxICON_ERROR);
        return;
    }
    sqlite3* db = openDatabase("ingrediente.db");
    if(!db) {
        wxMessageBox("Failed to open database", "Error", wxOK | wxICON_ERROR);
        return;
    }
    Reteta reteta = getRecipeById(db, recipeId);
    vector<tuple<string, double, string>> ingredients = getIngredientsForRecipe(db, recipeId);
    vector<Instructiune> instructiuni = getPreparationStepsForRecipe(db, recipeId);
    map<string, double> nutritionalValues = calculateNutritionalValue(db, recipeId);

    listBox->Clear();
    listBox->Append(wxString::Format("ID: %d, Name: %s", reteta.id, reteta.nume));
    listBox->Append(wxString::Format("Preparation Time: %d minutes", reteta.durata_preparare));
    listBox->Append(wxString::Format("Portions: %d", reteta.portii));
    listBox->Append(wxString::Format("Dieet type: %s", reteta.tip_dieta));
    listBox->Append("Ingredients: ");
    for(const auto& ingredient : ingredients) {
        listBox->Append(wxString::Format(" - %s: %.2f %s",
            get<0>(ingredient), get<1>(ingredient), get<2>(ingredient)));
    }
    listBox->Append("Instructions: ");
    for(const auto& instructiune : instructiuni) {
        listBox->Append(wxString::Format("  Step %d: %s", instructiune.pas, instructiune.descriere));
    }
    listBox->Append("Nutritional Values: ");
    listBox->Append(wxString::Format("  Energie: %.2f kJ, %.2f kcal", nutritionalValues["energie_kj"], nutritionalValues["energie_kcal"]));
    listBox->Append(wxString::Format("  Proteine: %.2f g", nutritionalValues["proteine"]));
    listBox->Append(wxString::Format("  Grasimi totale: %.2f g", nutritionalValues["grasimi_totale"]));
    listBox->Append(wxString::Format("  Grasimi saturate: %.2f g", nutritionalValues["grasimi_saturate"]));
    listBox->Append(wxString::Format("  Grasimi nesaturate: %.2f g", nutritionalValues["grasimi_nesaturate"]));
    listBox->Append(wxString::Format("  Carbohidrati: %.2f g", nutritionalValues["carbohidrati"]));
    listBox->Append(wxString::Format("  Zahar: %.2f g", nutritionalValues["zahar"]));

    sqlite3_close(db);
}

void MainFrame::OnRecommendRecipes(wxCommandEvent& event) {
    // Implement the logic to recommend recipes
    wxTextEntryDialog dialog(this, "Enter your available ingredients (comma separated):", "Recommend Recipes");
    if (dialog.ShowModal() == wxID_OK) {
        wxString ingredientsStr = dialog.GetValue().Lower();
        wxArrayString ingredientsArray = wxStringTokenize(ingredientsStr, ",");
        vector<string> ingredients;
        for (const auto& ingredient : ingredientsArray) {
            string normalizedIngredient = removeDiacritics(string(ingredient.mb_str()));
            ingredients.push_back(normalizedIngredient);
        }

        UserPreferences preferences;
        preferences.availableIngredients = ingredients;

        sqlite3* db = openDatabase("ingrediente.db");
        if (!db) {
            wxMessageBox("Failed to open database", "Error", wxOK | wxICON_ERROR);
            return;
        }

        vector<Reteta> recommendedRecipes = recommendRecipesContentBased(db, preferences);
        listBox->Clear();
        for (const auto& reteta : recommendedRecipes) {
            listBox->Append(wxString::Format("ID: %d, Name: %s", reteta.id, reteta.nume));
        }


        sqlite3_close(db);
        ShowSearchControls(false, false);
    }
}

void MainFrame::OnClassifyRecipe(wxCommandEvent& event) {
    int selection = listBox->GetSelection();
    if (selection == wxNOT_FOUND) {
        wxMessageBox("No recipe selected", "Error", wxOK | wxICON_ERROR);
        return;
    }
    wxString selectedRecipe = listBox->GetString(selection);
    long recipeId;
    if (!selectedRecipe.BeforeFirst(',').AfterFirst(':').ToLong(&recipeId)) {
        wxMessageBox("Invalid recipe ID", "Error", wxOK | wxICON_ERROR);
        return;
    }

    sqlite3* db = openDatabase("ingrediente.db");
    if (!db) {
        wxMessageBox("Failed to open database", "Error", wxOK | wxICON_ERROR);
        return;
    }

    // Antrenează modelul
    trainDecisionTreeModel(db);

    // Clasifică rețeta selectată
    mlpack::DecisionTree<>tree;
    mlpack::data::Load("decision_tree_model.xml", "tree", tree);

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


    classifyRecipe(db, recipeId);
    sqlite3_close(db);
}

void MainFrame::OnClusterRecipes(wxCommandEvent& event) {
    wxTextEntryDialog dialog(this, "Enter the number of clusters (k):", "K-Means Clustering");
    if (dialog.ShowModal() == wxID_OK) {
        long k;
        if (!dialog.GetValue().ToLong(&k) || k <= 0) {
            wxMessageBox("Invalid number of clusters", "Error", wxOK | wxICON_ERROR);
            return;
        }

        sqlite3* db = openDatabase("ingrediente.db");
        if (!db) {
            wxMessageBox("Failed to open database", "Error", wxOK | wxICON_ERROR);
            return;
        }

        vector<int> clusterAssignments = performKMeansClustering(db, k);
        vector<Reteta> retete = readRecipes(db);

        listBox->Clear();
        for (size_t i = 0; i < retete.size(); ++i) {
            listBox->Append(wxString::Format("ID: %d, Name: %s, Cluster: %d", retete[i].id, retete[i].nume, clusterAssignments[i]));
        }

        sqlite3_close(db);
    }
}