
#ifndef DECISIONTREECLASSIFIER_H
#define DECISIONTREECLASSIFIER_H

#include <mlpack/core.hpp>
#include <mlpack/methods/decision_tree/decision_tree.hpp>
#include <sqlite3.h>
#include <armadillo>

arma::mat prepareData(sqlite3* db, arma::Row<size_t>& labels);
void trainDecisionTreeModel(sqlite3* db);
void classifyRecipe(sqlite3* db, int recipeId);

#endif //DECISIONTREECLASSIFIER_H
