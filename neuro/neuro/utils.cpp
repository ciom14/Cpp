#include "utils.h"

void updateParameter(double& param, std::function<double()> computeError, double learningRate) {
    double delta = 0.001;
    double original = param;

    param = original + delta;
    double errorPlus = computeError();

    param = original - delta;
    double errorMinus = computeError();

    param = original;

    double gradient = (errorPlus - errorMinus) / (2 * delta);
    param -= learningRate * gradient;
}