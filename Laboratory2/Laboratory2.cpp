#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <windows.h>
#include "network.h"

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    srand(time(0));

    Network net({ 8, 4, 1 }, 2);

    // Генерируем точки
    int pointCount = 100;
    std::vector<Matrix> inputs;
    std::vector<double> expected;

    for (int i = 0; i < pointCount; i++) {
        double x = (double)rand() / RAND_MAX * 4 - 2; // от -2 до 2
        double y = (double)rand() / RAND_MAX * 4 - 2; // от -2 до 2

        Matrix input(1, 2);
        input.data[0][0] = x;
        input.data[0][1] = y;
        inputs.push_back(input);

        // Если y > sin(x) — класс 1, иначе класс 0
        expected.push_back(y > sin(x) ? 1.0 : 0.0);
    }

    // Обучаем
    std::ofstream lossFile("loss.txt");
    for (int epoch = 0; epoch < 1000; epoch++) {
        double totalLoss = 0.0;
        for (int i = 0; i < pointCount; i++) {
            net.train(inputs[i], expected[i], 0.1);
            totalLoss += net.mse(net.forward(inputs[i]).data[0][0], expected[i]);
        }
        totalLoss /= pointCount;

        if (epoch % 100 == 0)
            std::cout << "Epoch " << epoch << " loss: " << totalLoss << std::endl;
        lossFile << epoch << " " << totalLoss << std::endl;
    }
    lossFile.close();

    // Сохраняем точки для визуализации
    std::ofstream pointsFile("points.txt");
    for (int i = 0; i < pointCount; i++) {
        double x = inputs[i].data[0][0];
        double y = inputs[i].data[0][1];
        double pred = net.forward(inputs[i]).data[0][0];
        pointsFile << x << " " << y << " " << expected[i] << " " << pred << std::endl;
    }
    pointsFile.close();

    // Генерируем сетку для визуализации границы
    std::ofstream gridFile("grid.txt");
    int gridSize = 50;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            double x = -2.0 + 4.0 * i / (gridSize - 1);
            double y = -2.0 + 4.0 * j / (gridSize - 1);
            Matrix gridInput(1, 2);
            gridInput.data[0][0] = x;
            gridInput.data[0][1] = y;
            double pred = net.forward(gridInput).data[0][0];
            gridFile << x << " " << y << " " << pred << std::endl;
        }
    }
    gridFile.close();

    std::cout << "Done!" << std::endl;
}