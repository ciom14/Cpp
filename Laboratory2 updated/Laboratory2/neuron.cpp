#include "neuron.h"
#include "utils.h"
#include <cmath>
#include <cstdlib>

Neuron::Neuron(int inputSize) : weights(1, inputSize), bias(0.0) {
    for (int i = 0; i < inputSize; i++)
        weights.data[0][i] = (double)rand() / RAND_MAX * 2 - 1;
}

double Neuron::activate(double x) const {
    return 1.0 / (1.0 + exp(-x));
}

double Neuron::forward(const Matrix& input) const {
    Matrix result = weights * input.transpose();
    return activate(result.data[0][0] + bias);
}

double Neuron::mse(double predicted, double expected) const {
    double error = predicted - expected;
    return error * error;
}

void Neuron::train(const Matrix& input, double expected, double learningRate) {
    for (int w = 0; w < weights.cols; w++)
        updateParameter(weights.data[0][w], [&]() {
        return mse(forward(input), expected);
            }, learningRate);

    updateParameter(bias, [&]() {
        return mse(forward(input), expected);
        }, learningRate);
}