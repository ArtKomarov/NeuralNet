#ifndef MATRIX_H
#define MATRIX_H

/** \file matrix.h
 *  \brief Matrix class.
 *
 *  Matrix class describes operations with matrices.
*/

#include <vector>
#include <iostream>

typedef double matrix_t;


class Matrix {
    size_t    rows_;    /**< Number of matrix rows */
    size_t    columns_; /**< Number of matrix columns */
    matrix_t* matrix_;  /**< Matrix with 2 dimentions */
public:
    /// Default constructor 
    Matrix();

    /// Empty constructor rows x columnts size
    Matrix(size_t rows, size_t columns);

    /// Repeated num constructor rows x columns size
    Matrix(size_t rows, size_t columns, matrix_t num);

    /// Constructor column.size() x 1 matrix, equal to column
    Matrix(std::vector<matrix_t> column);

    /// Copy constructor
    Matrix(const Matrix &m);

    /// Move constructor
    Matrix(Matrix &&m);


    /// Get number of matrix rows
    size_t getRows() const;

    /// Get number of columns
    size_t getColumns() const;

    /// Get matrix size (\f$rows \cdot columns\f$)
    size_t size() const;


    const Matrix& operator = (const Matrix&  m);
    const Matrix& operator = (      Matrix&& m);

    const Matrix& operator += (const Matrix& m);
    const Matrix& operator -= (const Matrix& m);
    const Matrix& operator *= (const Matrix& m);

    Matrix operator * (const Matrix& m) const;
    Matrix operator + (const Matrix& m) const;
    Matrix operator - (const Matrix& m) const;

    Matrix operator + (const matrix_t num) const;
    Matrix operator - (const matrix_t num) const;
    Matrix operator * (const matrix_t num) const;
    Matrix operator / (const matrix_t num) const;

    friend Matrix operator + (const matrix_t num, const Matrix& m);
    friend Matrix operator - (const matrix_t num, const Matrix& m);
    friend Matrix operator * (const matrix_t num, const Matrix& m);

    friend const Matrix& operator + (const Matrix& m);
    friend       Matrix  operator - (const Matrix& m);

    /// Get "index" row
          matrix_t* operator [] (int index);

    /// Get "index" row
    const matrix_t* operator [] (int index) const;

    bool operator == (const Matrix& m) const;
    bool operator != (const Matrix& m) const;

    friend std::ostream& operator << (std::ostream& os, const Matrix& m);


    /// Summary of matrix elements
    matrix_t sum()   const;

    /// Summary of all columns in every row
    Matrix sum_X() const;

    /// Summary of all rows in every column
    Matrix sum_Y() const;


    /// Transpose matrix
    Matrix transpose() const;

    /// Fill matrix by random numbers 
    void fillRandom();

    /// Fill matrix by num
    void fillByNum(matrix_t num);


    /// Destructor
    ~Matrix();

    /// Create square diagonal matrix, where num on main diagonal
    friend Matrix Diagonal(size_t rows, matrix_t num);
};

#endif // MATRIX_H
