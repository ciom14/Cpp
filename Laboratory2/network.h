#pragma once
#include "layer.h"
#include <vector>

class Network {
public:
    std::vector<Layer> layers;

    Network(std::vector<int> layerSizes, int inputSize);
    Matrix forward(const Matrix& input) const;
    double mse(double predicted, double expected) const;
    void train(const Matrix& input, double expected, double learningRate);
};