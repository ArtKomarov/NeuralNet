#include <iostream>
#include <cmath>
#include <vector>

//#include "matrix.h"
//#include "functions.h"

#include "net.h"

typedef int Neuron;
//typedef long double ld;

int main () {
    // Task 1: y = 3x + 2
    std::vector<size_t> neuronsNum(2);
    neuronsNum[0] = 1;
    neuronsNum[1] = 1;

    Net net1(neuronsNum);

    // Fill training data
    Matrix X(3, 1);
    Matrix y(3, 1);
    X[0][0] = 1;
    y[0][0] = 5;

    X[1][0] = 3;
    y[1][0] = 11;

    X[2][0] = 4;
    y[2][0] = 14;

    Matrix lossHist = net1.train(X, y);

    std::cout << "Loss history:\n" << lossHist << std::endl;

    std::cout << net1.forward(X) << std::endl;

    return 0;
}
