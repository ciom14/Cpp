#pragma once
#include <functional>

void updateParameter(double& param, std::function<double()> computeError, double learningRate);