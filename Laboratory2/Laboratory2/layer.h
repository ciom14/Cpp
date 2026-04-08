#pragma once
#include "neuron.h"
#include <vector>

class Layer {
public:
    std::vector<Neuron> neurons;

    Layer(int neuronCount, int inputSize);
    Matrix forward(const Matrix& input) const;
};