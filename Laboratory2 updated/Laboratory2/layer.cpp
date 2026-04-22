#include "layer.h"

Layer::Layer(int neuronCount, int inputSize) {
    for (int i = 0; i < neuronCount; i++)
        neurons.push_back(Neuron(inputSize));
}

Matrix Layer::forward(const Matrix& input) const {
    Matrix result(1, neurons.size());
    for (int i = 0; i < neurons.size(); i++)
        result.data[0][i] = neurons[i].forward(input);
    return result;
}