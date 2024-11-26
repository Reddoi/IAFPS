//
// Created by Admin on 12.11.2024.
//

#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);

private:
    wxListBox* listBox;
    wxTextCtrl* searchCtrl;
    wxButton* searchButton;
    wxButton* classifyButton;
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnShowRecipes(wxCommandEvent& event);
    void OnSearchRecipe(wxCommandEvent& event);
    void OnFilterByCategory(wxCommandEvent& event);
    void OnFilterByDiet(wxCommandEvent& event);
    void OnSortByName(wxCommandEvent& event);
    void OnSortByPreparationTime(wxCommandEvent& event);
    void OnShowAllIngredients(wxCommandEvent& event);
    void OnRightClick(wxMouseEvent& event);
    void OnShowRecipeDetails(wxCommandEvent& event);
    void OnRecommendRecipes(wxCommandEvent& event);
    void OnSearchIngredient(wxCommandEvent& event);
    void ShowSearchControls(bool show, bool showClassifyButton);
    void OnClassifyRecipe(wxCommandEvent& event);
    void OnClusterRecipes(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

enum {
    ID_ShowRecipes = 1,
    ID_SearchRecipe,
    ID_FilterByCategory,
    ID_FilterByDiet,
    ID_SortByName,
    ID_SortByPreparationTime,
    ID_ShowAllIngredients,
    ID_ShowRecipeDetails,
    ID_RecommendedRecipes,
    ID_ClassifyRecipe,
    ID_ClusterRecipes
};


#endif //MAINFRAME_H
