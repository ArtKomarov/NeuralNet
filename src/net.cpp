//#include <limits>
//#include <cassert>

#include "net.h"

Net::Net (const std::vector<size_t>& neuronsInLayers, const std::vector<std::string>& activatonFunctionsNames) :
    layers_(neuronsInLayers.size()),
    activation_(activatonFunctionsNames.size()),
    funcValues_(neuronsInLayers.size()),
    grads_(neuronsInLayers.size()) {

    if (neuronsInLayers.size() != activatonFunctionsNames.size() + 1) {
        std::cerr << "ERROR: size of neuronsInLayers vector must be"
                     " equal to activatonFunctionsNames vector size + 1!" << std::endl;

        exit(-1); // TODO: create loyal option :D
    }


    for (size_t i = 0; i < layers_.size() - 1; ++i) {
        Matrix& layer_i = layers_[i];
        layer_i = Matrix(neuronsInLayers[i], neuronsInLayers[i + 1]);

        layers_[i].fillRandom();

        if (activatonFunctionsNames[i] == "sigmoid")
            activation_[i] = sigmoid;
//        for(size_t j1 = 0; j1 < neuronsInLayers[i]; j1++) {
//            for(size_t j2 = 0; j2 < neuronsInLayers[i + 1]; j2++)
//                layer_i[j1][j2] = static_cast<double>(rand()) /
//                        static_cast<double>(std::numeric_limits<int>::min());
//        }

    }

    size_t lastLayerNum = layers_.size() - 1;
    layers_[lastLayerNum] = Matrix(neuronsInLayers[lastLayerNum], 1);
    layers_[lastLayerNum].fillRandom();
}



//// TODO
//Matrix Net::forward(const Matrix &X) {
//    funcValues_[0] = sigmoid(X * layers_[0]);
//    std::cout << "[DEBUG] (func " << __FUNCTION__ << ") funcValues_[" << 0 << "] = " << funcValues_[0] << std::endl;

//    for(size_t i = 1; i < layers_.size() - 1; ++i) {
//        funcValues_[i] = sigmoid(funcValues_[i-1] * layers_[i]);
//        std::cout << "[DEBUG] (func " << __FUNCTION__ << ") funcValues_[" << i << "] = " << funcValues_[i] << std::endl;
//    }

//    size_t lastLayersNum = layers_.size() - 1;
//    funcValues_[lastLayersNum] = funcValues_[lastLayersNum - 1] * layers_[lastLayersNum];

//    return funcValues_.back();
//}

//void Net::backward (const Matrix &y) {
//    // Zero grad
//    for(size_t i = 0; i < grads_.size(); ++i)
//        grads_[i] = Matrix(layers_[i].getRows(), layers_[i].getColumns(), 1.);

//    // d(logloss) / dw = X.T * (p - y)
//    //(last activate func y=x) =>
//    //grads_[grads_.size() - 1] = funcValues_[funcValues_.size() - 2].transpose() *
//    //                            (funcValues_[funcValues_.size() - 1] - y); // deleted sumX() 2 times
//    grads_[grads_.size() - 1] = funcValues_[funcValues_.size() - 1];

//    std::cout << "[DEBUG] (func " << __FUNCTION__ << ") grads_[" << grads_.size() - 1 << "] = " << grads_[grads_.size() - 1] << std::endl;

//    Matrix dfunc = layers_.back(); // (last activate func y=x) = (funcValues_[funcValues_.size() - 1] - y).sum_X().sum_Y() *
//                  //layers_.back().transpose();                                 // added sum_Y() (?)

//    for(size_t i = 0; i < grads_.size(); ++i)
//        grads_[i] = grads_[i] * dfunc;

//    for(int i = grads_.size() - 2; i > 0; --i) {
//        grads_[i] = grads_[i] * derivativeSigmoid(layers_[i], funcValues_[i]);

//        dfunc = derivativeSigmoid(funcValues_[i-1], funcValues_[i]);

//        std::cout << "[DEBUG] (func " << __FUNCTION__ << ") grads_[" << i << "] = " << grads_[i] << std::endl;

//        for(int j = i - 1; j >= 0; --j)
//            grads_[j] = grads_[j] * dfunc;

//    }

//    // first layer
//    grads_[0] = grads_[0] * derivativeSigmoid(layers_[0], funcValues_[0]).sum_Y();
//    std::cout << "[DEBUG] (func " << __FUNCTION__ << ") grads_[" << 0 << "] = " << grads_[0] << std::endl;

//}

//// Calculate loss
//double Net::loss (const Matrix &y) const {
//    return logLoss(y, funcValues_.back());
//}

//// Update weights
//void Net::step(double lr) {
//    assert(layers_.size() == grads_.size());
//    for(size_t i = 0; i < layers_.size(); i++) {
//        layers_[i] -= lr * grads_[i];

//        std::cout << "[DEBUG] (func " << __FUNCTION__ << ") grads_[" << i << "] = " << lr * grads_[i] << std::endl;
//        std::cout << "[DEBUG] (func " << __FUNCTION__ << ") layers_[" << i << "] = " << layers_[i] << std::endl;
//    }
//}

//// Training loop
//std::vector<double> Net::train (const Matrix &X, const Matrix &y, size_t epochs, double lr) {
//     assert(layers_.size() == funcValues_.size());
//     assert(layers_.size() == grads_.size());
//    // Add b
//    Matrix X_train = X;
//    for(size_t i = 0; i < X.getRows(); ++i) {
//        X_train[i].push_back(1.);
//    }

//    std::vector<double> lossHist;

////    // Set gradients to zero
////    for(int i = 0; i < grads_->size(); i++) {
////        grads_[i] = 0;
////    }

//    // Start training
//    for(size_t e = 0; e < epochs; e++) {
//        this->forward(X_train);

//        lossHist.push_back(this->loss(y));

//        this->backward(y);

//        this->step(lr);

//    }
//    return lossHist;
//}

Net::~Net() {
    std::cout << "[DEBUG] " << __PRETTY_FUNCTION__ << std::endl;
}
