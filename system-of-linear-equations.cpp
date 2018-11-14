//
// Created by krutna on 14.09.18.
//

#include "system-of-linear-equations.hpp"

static void getDecreasedMatrix(
        std::vector<std::vector<double>>* matrix,
        std::vector<std::vector<double>>* matr,
        int i, int j, int m) {
    int ki, kj, di, dj;
    di = 0;
    for (ki = 0; ki < m-1; ++ki) {
        if (ki == i) di = 1;
        dj = 0;
        for (kj = 0; kj < m-1; ++kj) {
            if (kj == j) dj =1;
            (*matr)[ki][kj] = (*matrix)[ki + di][kj + dj];
        }
    }
}

static double getDeterminant(
        std::vector<std::vector<double>>* matrix, int dimension) {
    std::vector<std::vector<double>> matr;
    if (dimension == 1) {
        return (*matrix)[0][0];
    }
    if (dimension == 2) {
        return (*matrix)[0][0] * (*matrix)[1][1] -
               (*matrix)[0][1] * (*matrix)[1][0];
    }
    int k = 1;
    int determinant = 0;
    for (int i = 0; i < dimension-1; ++i) {
        matr.emplace_back();
        for (int j = 0; j < dimension-1; ++j)
            matr[i].emplace_back();
    }
    for (int i = 0; i < dimension; ++i) {
        getDecreasedMatrix(matrix, &matr, i, 0, dimension);
        determinant += k * (*matrix)[i][0] * getDeterminant(&matr, dimension-1);
        k = -k;
    }
    return determinant;
}

bool SystemOfLinearEquations::executeMethod(std::vector<std::vector<double>> *matrix, int dimension, std::ofstream* outFile) {
    bool result = false;
    std::vector<double> x;
    double determinant = getDeterminant(matrix, dimension);
    double temp = 0;
    std::vector<std::string> tempVector;
    std::vector<double> discrepancies;
    std::vector<std::vector<double>> matr;

    for (int i = 0; i < dimension; i++) {
        matr.emplace_back();
        for (int j = 0; j < dimension + 1; j++)
            matr[i].push_back((*matrix)[i][j]);
    }

    if (determinant != determinant) {
        std::cout << "Can't count determinant!" << std::endl;
        goto resultLabel;
    }
    temp = getDeterminant(matrix, dimension);
    std::cout << "Determinant: " << temp << std::endl;
    if (temp == 0) {
        std::cout << "Matrix is singular: has 0 or many solves" << std::endl;
        goto resultLabel;
    }
    if (outFile->is_open()) {
        temp = getDeterminant(matrix, dimension);
        tempVector.emplace_back("Determinant: ");
        tempVector.push_back(std::to_string(temp));
        tempVector.emplace_back("\n");
    }
    tempVector.clear();
    for (int i = 0; i < dimension; ++i)
        x.emplace_back();
    for (int k = 1; k < dimension; ++k) {
        for (int j = k; j < dimension; ++j) {
            double m = (*matrix)[j][k - 1] / (*matrix)[k - 1][k - 1];
            for (int i = 0; i < dimension + 1; ++i) {
                (*matrix)[j][i] = (*matrix)[j][i] - m * (*matrix)[k - 1][i];
                if ((*matrix)[j][i] != (*matrix)[j][i]) {
                    std::cout << "Error occurred on translating to triangular form!" << std::endl;
                    goto resultLabel;
                }
            }
        }
    }
    std::cout << "Triangular form:\n";
    if (outFile->is_open()) {
        tempVector.emplace_back("Triangular form:\n");
    }
    for (int i = 0; i < dimension; ++i) {
        std::cout << "| ";
        for (int j = 0; j < dimension+1; ++j) {
            std::cout << (*matrix)[i][j] << " ";
            if (outFile->is_open()) {
                tempVector.push_back(std::to_string((*matrix)[i][j]));
                tempVector.emplace_back(" ");
            }
        }
        std::cout << std::endl;
        if (outFile->is_open())
            tempVector.emplace_back("\n");
    }

    for (int i = dimension-1; i >= 0; --i) {
        x[i] = (*matrix)[i][dimension] / (*matrix)[i][i];
        for (int c = dimension-1; c > i; --c)
            x[i] = x[i] - (*matrix)[i][c] * x[c] / (*matrix)[i][i];
    }

    std::cout << "Results: [ ";
    if (outFile->is_open()) tempVector.emplace_back("Results: [ ");
    for (int i = 0; i < dimension; ++i) {
        std::cout << x[i] << " ";
        if (outFile->is_open()) {
            tempVector.push_back(std::to_string(x[i]));
            tempVector.emplace_back(" ");
        }
    }
    std::cout << "]\nDiscrepancies: [ ";
    if (outFile->is_open()) tempVector.emplace_back("]\nDiscrepancies: [ ");
    for (int i = 0; i < dimension; ++i) {
        double a = 0;
        for (int j = 0; j < dimension; ++j) {
            a += matr[i][j] * x[j];
        }
        std::cout << a - matr[i][dimension] << " ";
        if (outFile->is_open()) {
            tempVector.push_back(std::to_string(a-matr[i][dimension]));
            tempVector.emplace_back(" ");
        }
    }
    std::cout << "]" << std::endl;
    if (outFile->is_open()) {
        tempVector.emplace_back("]\n");
        for (auto &i : tempVector) {
            outFile->write(i.data(), i.size());
        }
    }
resultLabel:
    return result;
}