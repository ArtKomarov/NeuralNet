#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "matrix.h"

/** \file functions.h
 *  \brief File with functions, used in neural net.
 *
 *  There are activation functions, loss functions, functions gradients.
 *
 *  \warning Matrix_t must be double for most of functions usage.
*/

/// Sigmoid function (1 / (1 + exp(-t)))
double sigmoid(double val);

/// Matrix sigmoid function (1 / (1 + exp(-t)))
Matrix sigmoid(const Matrix& m);

/// Derivative of the sigmoid
Matrix gradSigmoid(const Matrix& W, const Matrix& X);

/// Use function to every element in matrix m
Matrix funcToMatrix(const Matrix& m, double (*func)(double));

/// Logistic loss function (for binary classification)
double logLoss(const Matrix& y_real, const Matrix& y_pred);

#endif // FUNCTIONS_H
