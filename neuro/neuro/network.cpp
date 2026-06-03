#include "network.h"
#include "utils.h"
#include <fstream>

Network::Network(std::vector<int> layerSizes, int inputSize) {
    int currentInputSize = inputSize;
    for (int i = 0; i < layerSizes.size(); i++) {
        layers.push_back(Layer(layerSizes[i], currentInputSize));
        currentInputSize = layerSizes[i];
    }
}

Matrix Network::forward(Matrix input) const {
    for (int i = 0; i < layers.size(); i++)
        input = layers[i].forward(input);
    return input;
}

double Network::mse(double predicted, double expected) const {
    double error = predicted - expected;
    return error * error;
}

void Network::train(const Matrix& input, double expected, double learningRate) {
    for (int l = 0; l < layers.size(); l++)
        for (int n = 0; n < layers[l].neurons.size(); n++) {
            for (int w = 0; w < layers[l].neurons[n].weights.cols; w++)
                updateParameter(layers[l].neurons[n].weights.data[0][w], [&]() {
                return mse(forward(input).data[0][0], expected);
                    }, learningRate);

            updateParameter(layers[l].neurons[n].bias, [&]() {
                return mse(forward(input).data[0][0], expected);
                }, learningRate);
        }
}

void Network::save(const std::string& filename) const {
    std::ofstream file(filename);
    for (int l = 0; l < layers.size(); l++) {
        for (int n = 0; n < layers[l].neurons.size(); n++) {
            for (int w = 0; w < layers[l].neurons[n].weights.cols; w++) {
                file << layers[l].neurons[n].weights.data[0][w] << " ";
            }
            file << layers[l].neurons[n].bias << "\n";
        }
    }
}

void Network::load(const std::string& filename) {
    std::ifstream file(filename);
    for (int l = 0; l < layers.size(); l++) {
        for (int n = 0; n < layers[l].neurons.size(); n++) {
            for (int w = 0; w < layers[l].neurons[n].weights.cols; w++) {
                file >> layers[l].neurons[n].weights.data[0][w];
            }
            file >> layers[l].neurons[n].bias;
        }
    }
}