#include "matrix.h"

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    data = std::vector<std::vector<double>>(rows, std::vector<double>(cols, 0.0));
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Размеры матриц не совпадают");
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.data[i][j] = data[i][j] + other.data[i][j];
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows)
        throw std::invalid_argument("Нельзя перемножить эти матрицы");
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < other.cols; j++)
            for (int k = 0; k < cols; k++)
                result.data[i][j] += data[i][k] * other.data[k][j];
    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.data[j][i] = data[i][j];
    return result;
}
