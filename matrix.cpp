#include <iostream>
#include <new>
#include <limits>

#include "matrix.h"

// Constructors
Matrix::Matrix () :
    Matrix(0, 0) {
}

Matrix::Matrix (size_t rows, size_t columns) :
    rows_(rows),
    columns_(columns),
    matrix_(new mtx(rows, std::vector<double>(columns))) { // ?
}

Matrix::Matrix(size_t rows, size_t columns, double num) :
    Matrix(rows, columns) {

    for(size_t i = 0; i < rows_; i++) {
        std::vector<double>& this_row = (*this)[i];
        for(size_t j = 0; j < columns_; j++)
            this_row[j] = num;
    }
}

Matrix::Matrix (std::vector<double> column) :
    Matrix(static_cast<size_t>(column.size()), 1) {

    for(size_t i = 0; i < this->getRows(); i++)
        (*this)[i][0] = column[i];
}

Matrix::Matrix (const Matrix &m) :
    Matrix(m.rows_, m.columns_) {
    for(size_t i = 0; i < rows_; i++) {
        std::vector<double>& this_row    = this->operator [](i);
        const std::vector<double>& m_row = m[i];

        for(size_t j = 0; j < columns_; j++)
            this_row[j] = m_row[j];
    }
}

Matrix::Matrix (Matrix &&m) :
    rows_    (m.rows_),
    columns_ (m.columns_),
    matrix_  (m.matrix_) {
    m.matrix_ = nullptr;
}

// Gettersresult
size_t Matrix::getRows() const {
    return rows_;
}

size_t Matrix::getColumns() const {
    return columns_;
}

size_t Matrix::size() const {
    return rows_ * columns_;
}

// Operators
const Matrix &Matrix::operator = (const Matrix &m) {
    delete matrix_;
    return *new (this) Matrix(m);
}

const Matrix &Matrix::operator = (Matrix &&m) {
    delete matrix_;
    return *new (this) Matrix(m);
}

Matrix Matrix::operator * (const Matrix &m) const {
    return Matrix(*this) *= m;
}

const Matrix& Matrix::operator *= (const Matrix& m) {
    if(columns_ != m.rows_) {
        std::cerr << __PRETTY_FUNCTION__
                  << ": can not multiply matrices with dimentions: "
                  << rows_ << "x" << columns_ << " and "
                  << m.rows_ << "x" << m.columns_ << std::endl;
        return *this;
    }

    Matrix this_copy(std::move(*this)); // must move this->matrix_ memory
    //Matrix result(rows_, m.columns_);

    new (this) Matrix (this_copy.rows_, m.columns_);

    for(size_t row = 0; row < this_copy.rows_; row++) {
        const std::vector<double>& copy_row = this_copy[row];
        std::vector<double>&       this_row = (*this)[row];

        for(size_t col = 0; col < m.columns_; col++) {
            this_row[col] = 0;

            for(size_t i = 0; i < this_copy.columns_; i++)
                this_row[col] += copy_row[i] * (*m.matrix_)[i][col];
        }
    }


    return *this;
}

Matrix operator * (const double num, const Matrix &m) {
    return m * num;
}

Matrix Matrix::operator * (const double num) const {
    Matrix result(rows_, columns_);

    std::cout << "[DEBUG] " << __FUNCTION__ << " this:\n" << *this;
    std::cout << "[DEBUG] " << __FUNCTION__ << " num:\n" << num;

    for(size_t row = 0; row < rows_; row++) {
        std::vector<double>&       result_row = result[row];
        const std::vector<double>& this_row   = (*this)[row];

         for(size_t col = 0; col < columns_; col++) {
             result_row[col] = num * this_row[col];
         }
    }

    std::cout << "[DEBUG] " << __FUNCTION__ << " result:\n" << result;

    return result;
}

Matrix Matrix::operator / (const double num) const {
    Matrix result(rows_, columns_);

    for(size_t row = 0; row < rows_; row++) {
        std::vector<double>&       result_row = result[row];
        const std::vector<double>& this_row   = (*this)[row];

         for(size_t col = 0; col < columns_; col++) {
             result_row[col] = num / this_row[col];
         }
    }

    return result;
}

// Define operator + and - (operand Matrix, double)
#define DEFINE_PLUS_MINUS(OP) \
    const Matrix& Matrix::operator OP##= (const Matrix &m) { \
        if(rows_ != m.rows_) {                               \
            std::cerr << __PRETTY_FUNCTION__ << ": "         \
                      << "Number of rows is not equal!"      \
                      << std::endl;                          \
            return *this;                                    \
        } \
          \
        if(columns_ != m.columns_) { \
            std::cerr << __PRETTY_FUNCTION__ << ": "       \
                      << "Number of columns is not equal!" \
                      << std::endl;                        \
            return *this;                                  \
        } \
                                                              \
        for(size_t i = 0; i < rows_; i++) {                   \
            std::vector<double>& this_row    = (*this)[i];    \
            const std::vector<double>& m_row = m[i];          \
                                                              \
            for(size_t j = 0; j < columns_; j++) {            \
                this_row[j] OP##= m_row[j];                   \
            }          \
        }              \
                       \
        return *this; \
    } \
      \
    Matrix Matrix::operator OP (const Matrix &m) const { \
        return Matrix(*this) OP##= m;                    \
    } \
      \
    Matrix Matrix::operator OP (const double num) const {     \
        Matrix result(rows_, columns_);                       \
                                                              \
        for(size_t i = 0; i < rows_; i++) {                   \
            const std::vector<double>& this_row = (*this)[i]; \
            std::vector<double>& res_row        = result[i];  \
                                                              \
            for(size_t j = 0; j < columns_; j++) {            \
                res_row[j] = this_row[j] OP num;              \
            }                                                 \
        }                                                     \
                                                              \
        return result;                                        \
    }                                                         \
                                                              \
    Matrix operator OP (const double num, const Matrix& m) {  \
        Matrix result(m.rows_, m.columns_);                   \
                                                              \
        for(size_t i = 0; i < m.rows_; i++) {                 \
            const std::vector<double>& m_row = m[i];          \
            std::vector<double>& res_row    = result[i];      \
                                                              \
            for(size_t j = 0; j < m.columns_; j++) {          \
                res_row[j] = num OP m_row[j];                 \
            }                                                 \
        }                                                     \
                                                              \
        return result;                                        \
    }

DEFINE_PLUS_MINUS(+)

DEFINE_PLUS_MINUS(-)

const Matrix &operator + (const Matrix &m) {
    return m;
}

Matrix operator - (const Matrix &m) {
    return (-1) * m;
}


//const Matrix& Matrix::operator += (const Matrix &m) {
//    if(rows_ != m.rows_) {
//        std::cerr << __PRETTY_FUNCTION__ << ": " << "Number of rows is not equal!" << std::endl;
//        return *this;
//    }

//    if(columns_ != m.columns_) {
//        std::cerr << __PRETTY_FUNCTION__ << ": " << "Number of columns is not equal!" << std::endl;
//        return *this;
//    }

//    //Matrix result(rows_, columns_);

//    for(size_t i = 0; i < rows_; i++) {
//        std::vector<double>& this_row    = (*this)[i];
//        const std::vector<double>& m_row = m[i];

//        //std::vector<double>& res_row        = result[i];

//        for(size_t j = 0; j < columns_; j++) {
//            this_row[j] += m_row[j];
//        }
//    }

//    return *this;
//}


// Get row
std::vector<double>& Matrix::operator [] (int index) {
    return (*matrix_)[index];
}

// Get const row from const matrix
const std::vector<double>& Matrix::operator [](int index) const {
    return (*matrix_)[index];
}

std::ostream& operator << (std::ostream &os, const Matrix &m) {
    for(size_t i = 0; i < m.rows_; i++) {
        const std::vector<double>& curRow = m[i];
        for(size_t j = 0; j < m.columns_; j++)
            os << curRow[j] << " ";
        os << std::endl;
    }
    return os;
}

// Summary of matrix elements
double Matrix::sum() const {
    double result = 0;

    for(size_t i = 0; i < rows_; i++) {
        const std::vector<double>& curRow = (*this)[i];

        for(size_t j = 0; j < columns_; j++)
            result += curRow[j];
    }

    return result;
}

Matrix Matrix::sum_X() const {
    Matrix result(rows_, 1);

    for(size_t i = 0; i < matrix_->size(); i++) {
        const std::vector<double>& curRow = (*this)[i];

        double& result_i = result[i][0];
        result_i = 0;

        for(size_t j = 0; j < curRow.size(); j++)
            result_i += curRow[j];
    }

    return result;
}

Matrix Matrix::sum_Y() const {
    Matrix result(1, columns_);
    std::vector<double>& result_row = result[0];

    for(size_t j = 0; j < columns_; j++)
        result_row[j] = 0;

    for(size_t i = 0; i < rows_; i++) {
        const std::vector<double>& curRow = (*this)[i];

        for(size_t j = 0; j < columns_; j++)
            result_row[j] += curRow[j];
    }

    return result;
}

// Transpose matrix
Matrix Matrix::transpose() const {
    Matrix result(columns_, rows_);

    for(size_t row = 0; row < rows_; row++) {
        const std::vector<double>& this_row   = (*this)[row];

         for(size_t col = 0; col < columns_; col++) {
             result[col][row] = this_row[col];
         }
    }

    return result;
}

void Matrix::fillRandom() {
    for(size_t i = 0; i < rows_; i++) {
        std::vector<double>& this_row = (*this)[i];
        for(size_t j = 0; j < columns_; j++)
            this_row[j] = static_cast<double>(rand()) /
                    static_cast<double>(std::numeric_limits<int>::min());
    }
}

void Matrix::fillByNum(double num) {
    for(size_t i = 0; i < rows_; i++) {
        std::vector<double>& this_row = (*this)[i];
        for(size_t j = 0; j < columns_; j++)
            this_row[j] = num;
    }
}

Matrix::~Matrix() {
    rows_    = 0;
    columns_ = 0;

    delete matrix_;

    matrix_ = nullptr;
}
