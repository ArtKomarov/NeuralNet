#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

typedef std::vector<std::vector<double>> mtx;

class Matrix {
    size_t rows_;    /**< Number of matrix rows */
    size_t columns_; /**< Number of matrix columns */
    mtx*   matrix_;  /**< Matrix with 2 dimentions */
public:
    /// Constructors
    Matrix ();
    Matrix (size_t rows, size_t columns);
    Matrix (size_t rows, size_t columns, double num);
    Matrix (std::vector<double> column);
    Matrix (const Matrix &m);
    Matrix (Matrix &&m);

    /// Getters
    size_t getRows()    const;
    size_t getColumns() const;
    size_t size() const;

    /// Operators
    const Matrix& operator = (const Matrix&  m);
    const Matrix& operator = (      Matrix&& m);

    const Matrix& operator += (const Matrix& m);
    const Matrix& operator -= (const Matrix& m);
    const Matrix& operator *= (const Matrix& m);

    Matrix operator * (const Matrix& m) const;
    Matrix operator + (const Matrix& m) const;
    Matrix operator - (const Matrix& m) const;

    Matrix operator + (const double num) const;
    Matrix operator - (const double num) const;
    Matrix operator * (const double num) const;
    Matrix operator / (const double num) const;

    friend Matrix operator + (const double num, const Matrix& m);
    friend Matrix operator - (const double num, const Matrix& m);
    friend Matrix operator * (const double num, const Matrix& m);

    friend const Matrix& operator + (const Matrix& m);
    friend       Matrix  operator - (const Matrix& m);

          std::vector<double> &operator [] (int index);
    const std::vector<double> &operator [] (int index) const;

    friend std::ostream& operator << (std::ostream& os, const Matrix& m);

    /// Summary of matrix elements
    double sum()   const;
    Matrix sum_X() const;
    Matrix sum_Y() const;

    /// Transpose matrix
    Matrix transpose() const;

    /// Other functions
    void fillRandom();
    void fillByNum(double num);

    ~Matrix();
};

#endif // MATRIX_H
