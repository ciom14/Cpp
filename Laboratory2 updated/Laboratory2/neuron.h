#pragma once
#include "matrix.h"

class Neuron {
public:
    Matrix weights;
    double bias;

    Neuron(int inputSize);
    double activate(double x) const;
    double forward(const Matrix& input) const;
    double mse(double predicted, double expected) const;
    void train(const Matrix& input, double expected, double learningRate);
};