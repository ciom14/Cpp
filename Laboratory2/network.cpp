#include "network.h"

Network::Network(std::vector<int> layerSizes, int inputSize) {
    int currentInputSize = inputSize;
    for (int i = 0; i < layerSizes.size(); i++) {
        layers.push_back(Layer(layerSizes[i], currentInputSize));
        currentInputSize = layerSizes[i];
    }
}

Matrix Network::forward(const Matrix& input) const {
    Matrix current = input;
    for (int i = 0; i < layers.size(); i++)
        current = layers[i].forward(current);
    return current;
}

double Network::mse(double predicted, double expected) const {
    double error = predicted - expected;
    return error * error;
}

void Network::train(const Matrix& input, double expected, double learningRate) {
    double delta = 0.001;

    for (int l = 0; l < layers.size(); l++) {
        for (int n = 0; n < layers[l].neurons.size(); n++) {
            for (int w = 0; w < layers[l].neurons[n].weights.cols; w++) {
                double original = layers[l].neurons[n].weights.data[0][w];

                layers[l].neurons[n].weights.data[0][w] = original + delta;
                double errorPlus = mse(forward(input).data[0][0], expected);

                layers[l].neurons[n].weights.data[0][w] = original - delta;
                double errorMinus = mse(forward(input).data[0][0], expected);

                layers[l].neurons[n].weights.data[0][w] = original;

                double gradient = (errorPlus - errorMinus) / (2 * delta);
                layers[l].neurons[n].weights.data[0][w] -= learningRate * gradient;
            }

            double original = layers[l].neurons[n].bias;

            layers[l].neurons[n].bias = original + delta;
            double errorPlus = mse(forward(input).data[0][0], expected);

            layers[l].neurons[n].bias = original - delta;
            double errorMinus = mse(forward(input).data[0][0], expected);

            layers[l].neurons[n].bias = original;

            double gradient = (errorPlus - errorMinus) / (2 * delta);
            layers[l].neurons[n].bias -= learningRate * gradient;
        }
    }
}