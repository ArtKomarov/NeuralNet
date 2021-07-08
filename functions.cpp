#include <cmath>

#include "functions.h"


double sigmoid (double val) {
    return 1. / (1. + std::exp(-val));
}

Matrix sigmoid (const Matrix& m) {
    Matrix result(m.getRows(), m.getColumns());
    for(size_t i = 0; i < m.getRows(); i++) {
        std::vector<double> &resRow     = result[i];
        const std::vector<double> &mRow = m[i];

        for(size_t j = 0; j < m.getColumns(); j++)
            resRow[j] = sigmoid(mRow[j]);

    }
    return result;
}

Matrix derivativeSigmoid(const Matrix& W, const Matrix& X) {
    Matrix y = sigmoid(X * W);
    return y * (1. - y.transpose()) * X; // X.transpose() -> X
}

Matrix funcToMatrix (const Matrix& m, double (*func)(double)) {
    Matrix result(m.getRows(), m.getColumns());
    for(size_t i = 0; i < m.getRows(); i++) {
        std::vector<double> &resRow     = result[i];
        const std::vector<double> &mRow = m[i];

        for(size_t j = 0; j < m.getColumns(); j++)
            resRow[j] = (*func)(mRow[j]);

    }
    return result;
}

double logLoss(const Matrix &y_real, const Matrix &y_pred) {
    return ( - y_real.transpose()       * funcToMatrix(y_pred,     std::log)
             - (1 - y_real).transpose() * funcToMatrix(1 - y_pred, std::log) ).sum();
}
