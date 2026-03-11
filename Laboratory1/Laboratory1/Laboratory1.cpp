#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "matrix.h"
#include "neuron.h"

int main() {
    srand(time(0));

    Neuron n(2);

    Matrix i00(1, 2); i00.data[0][0] = 0; i00.data[0][1] = 0;
    Matrix i01(1, 2); i01.data[0][0] = 0; i01.data[0][1] = 1;
    Matrix i10(1, 2); i10.data[0][0] = 1; i10.data[0][1] = 0;
    Matrix i11(1, 2); i11.data[0][0] = 1; i11.data[0][1] = 1;

    std::cout << "Do obucheniya:" << std::endl;
    std::cout << "[0,0] -> " << n.forward(i00) << std::endl;
    std::cout << "[0,1] -> " << n.forward(i01) << std::endl;
    std::cout << "[1,0] -> " << n.forward(i10) << std::endl;
    std::cout << "[1,1] -> " << n.forward(i11) << std::endl;

    std::ofstream file("loss.txt");

    for (int epoch = 0; epoch < 100000; epoch++) {
        n.train(i00, 0.0, 0.1);
        n.train(i01, 0.0, 0.1);
        n.train(i10, 0.0, 0.1);
        n.train(i11, 1.0, 0.1);

        if (epoch % 100 == 0) {
            double loss = n.mse(n.forward(i00), 0.0)
                + n.mse(n.forward(i01), 0.0)
                + n.mse(n.forward(i10), 0.0)
                + n.mse(n.forward(i11), 1.0);
            file << epoch << " " << loss << std::endl;

            if (epoch % 10000 == 0)
                std::cout << "Epoch " << epoch << " loss: " << loss << std::endl;
        }
    }

    file.close();

    std::cout << "\nPosle obucheniya:" << std::endl;
    std::cout << "[0,0] -> " << n.forward(i00) << std::endl;
    std::cout << "[0,1] -> " << n.forward(i01) << std::endl;
    std::cout << "[1,0] -> " << n.forward(i10) << std::endl;
    std::cout << "[1,1] -> " << n.forward(i11) << std::endl;

    std::cout << "\nVesa posle obucheniya:" << std::endl;
    std::cout << "w1: " << n.weights.data[0][0] << std::endl;
    std::cout << "w2: " << n.weights.data[0][1] << std::endl;
    std::cout << "bias: " << n.bias << std::endl;
}