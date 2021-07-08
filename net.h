#ifndef NET_H
#define NET_H

#include <vector>

#include "matrix.h"
#include "functions.h"

class Net {
    /// Neural network layers
    std::vector<Matrix> layers_;

    /// Values of activation functions (for backward)
    std::vector<Matrix> funcValues_;

    /// Gradients on every layer (for backward)
    std::vector<Matrix> grads_;

public:
    /// Constructor ///
    /// \brief Net
    /// \param neuronsInLayers: number of neurons in each layer
    Net (const std::vector<size_t> &neuronsInLayers);

    /// Forward X throught layers and activation functions
    virtual Matrix forward (const Matrix& X);

    /// Backpropagation
    virtual void backward (const Matrix &y);

    /// Calculate loss
    virtual double loss(const Matrix& y) const;

    /// Update weights
    virtual void step (double lr);

    /// Train loop
    std::vector<double> train (const Matrix& X, const Matrix& y, size_t epochs = 50, double lr = 1e-3);

    /// Destrucor
    virtual ~Net();
};

#endif // NET_H
