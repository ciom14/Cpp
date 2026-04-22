#pragma once
#include <vector>
#include <stdexcept>

class Matrix {
public:
    int rows;
    int cols;
    std::vector<std::vector<double>> data;

    Matrix(int rows, int cols);
    Matrix operator+(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix transpose() const;
};