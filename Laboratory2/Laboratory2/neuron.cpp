#include "neuron.h"
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
    double delta = 0.001;

    for (int i = 0; i < weights.cols; i++) {
        double originalWeight = weights.data[0][i];

        weights.data[0][i] = originalWeight + delta;
        double errorPlus = mse(forward(input), expected);

        weights.data[0][i] = originalWeight - delta;
        double errorMinus = mse(forward(input), expected);

        weights.data[0][i] = originalWeight;

        double gradient = (errorPlus - errorMinus) / (2 * delta);
        weights.data[0][i] -= learningRate * gradient;
    }

    double originalBias = bias;

    bias = originalBias + delta;
    double errorPlus = mse(forward(input), expected);

    bias = originalBias - delta;
    double errorMinus = mse(forward(input), expected);

    bias = originalBias;

    double gradient = (errorPlus - errorMinus) / (2 * delta);
    bias -= learningRate * gradient;
}