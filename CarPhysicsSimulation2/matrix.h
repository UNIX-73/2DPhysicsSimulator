#pragma once

#include <vector>
#include <iostream>

class Matrix {
private:
    std::vector<std::vector<double>> data;
    size_t rows, cols;

public:
    Matrix(const std::vector<std::vector<double>>& values);

    Matrix(size_t rows, size_t cols);


    // Obtener un valor en una posición
    double& operator()(size_t row, size_t col);
    const double& operator()(size_t row, size_t col) const;

    void PushRowBack(const std::vector<double>& row);
    void PushColBack(const std::vector<double>& col);

    void SetValue(int rowIdx, int colIdx, const double value);
    void AddValue(int rowIdx, int colIdx, const double value);


    void SetRow(int rowIdx, const std::vector<double>& row);

    static Matrix AdjustSize(const Matrix& smaller, size_t newRows);

    void appendColumn(const Matrix& colMatrix);

    void swapRows(int row1, int row2);

    void resize(size_t newRows, size_t newCols);


    // Obtener dimensiones
    size_t getRows() const;
    size_t getCols() const;

    double getValue(int row, int col) const;

    // Suma de matrices
    Matrix operator+(const Matrix& other) const;

    // Resta de matrices
    Matrix operator-(const Matrix& other) const;

    Matrix operator-() const;


    // Multiplicación de matrices
    Matrix operator*(const Matrix& other) const;

    Matrix operator*(const double& other) const;

    // Transposición de la matriz
    Matrix transpose() const;

    // Multiplicación de matriz por un vector
    std::vector<double> operator*(const std::vector<double>& vec) const;

    // Mostrar matriz
    void print() const;
};
