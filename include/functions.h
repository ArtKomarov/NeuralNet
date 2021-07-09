#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "matrix.h"

/// Sigmoid function (1 / (1 + exp(-t)))
double sigmoid (double val);
Matrix sigmoid (const Matrix& m);

/// Derivative of the sigmoid
Matrix derivativeSigmoid (const Matrix& W, const Matrix& X);

/// Use function to every element in matrix m
Matrix funcToMatrix (const Matrix& m, double (*func)(double));

/// Logistic loss function (for binary classification)
double logLoss (const Matrix& y_real, const Matrix& y_pred);

#endif // FUNCTIONS_H
