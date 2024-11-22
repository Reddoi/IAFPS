#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <vector>

class Simplex {
public:
    Simplex(const std::vector<std::vector<double>>& A, const std::vector<double>& b, const std::vector<double>& c);
    void solve();
    std::vector<double> getSolution();

private:
    std::vector<std::vector<double>> A;
    std::vector<double> b;
    std::vector<double> c;
    int m, n;
    std::vector<std::vector<double>> tableau;

    void initializeTableau();
    int findPivotColumn();
    int findPivotRow(int pivotCol);
    void pivot(int pivotRow, int pivotCol);
};

#endif // SIMPLEX_H