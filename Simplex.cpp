#include "Simplex.h"
#include <limits>
#include <iostream>

Simplex::Simplex(const std::vector<std::vector<double>>& A, const std::vector<double>& b, const std::vector<double>& c)
    : A(A), b(b), c(c), m(b.size()), n(c.size()) {
    initializeTableau();
}

void Simplex::initializeTableau() {
    tableau.resize(m + 1, std::vector<double>(n + m + 1, 0.0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            tableau[i][j] = A[i][j];
        }
        tableau[i][n + i] = 1.0;
        tableau[i][n + m] = b[i];
    }
    for (int j = 0; j < n; ++j) {
        tableau[m][j] = -c[j];
    }
}

int Simplex::findPivotColumn() {
    int pivotCol = 0;
    for (int j = 1; j < n + m; ++j) {
        if (tableau[m][j] < tableau[m][pivotCol]) {
            pivotCol = j;
        }
    }
    return pivotCol;
}

int Simplex::findPivotRow(int pivotCol) {
    int pivotRow = -1;
    double minRatio = std::numeric_limits<double>::max();
    for (int i = 0; i < m; ++i) {
        if (tableau[i][pivotCol] > 0) {
            double ratio = tableau[i][n + m] / tableau[i][pivotCol];
            if (ratio < minRatio) {
                minRatio = ratio;
                pivotRow = i;
            }
        }
    }
    return pivotRow;
}

void Simplex::pivot(int pivotRow, int pivotCol) {
    double pivotValue = tableau[pivotRow][pivotCol];
    for (int j = 0; j < n + m + 1; ++j) {
        tableau[pivotRow][j] /= pivotValue;
    }
    for (int i = 0; i < m + 1; ++i) {
        if (i != pivotRow) {
            double factor = tableau[i][pivotCol];
            for (int j = 0; j < n + m + 1; ++j) {
                tableau[i][j] -= factor * tableau[pivotRow][j];
            }
        }
    }
}

void Simplex::solve() {
    while (true) {
        int pivotCol = findPivotColumn();
        if (tableau[m][pivotCol] >= 0) {
            break;
        }
        int pivotRow = findPivotRow(pivotCol);
        if (pivotRow == -1) {
            throw std::runtime_error("Unbounded solution");
        }
        pivot(pivotRow, pivotCol);
    }
}

std::vector<double> Simplex::getSolution() {
    std::vector<double> solution(n, 0.0);
    for (int i = 0; i < m; ++i) {
        bool isBasic = true;
        int basicVar = -1;
        for (int j = 0; j < n; ++j) {
            if (tableau[i][j] == 1.0) {
                if (basicVar == -1) {
                    basicVar = j;
                } else {
                    isBasic = false;
                    break;
                }
            } else if (tableau[i][j] != 0.0) {
                isBasic = false;
                break;
            }
        }
        if (isBasic && basicVar != -1) {
            solution[basicVar] = tableau[i][n + m];
        }
    }
    return solution;
}