#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "network.h"

namespace py = pybind11;

PYBIND11_MODULE(neuro, m) {
    py::class_<Network>(m, "Network")
        .def(py::init<std::vector<int>, int>())
        .def("forward", [](Network& net, py::list input) {
        int size = (int)input.size();
        double* data = new double[size];
        for (int i = 0; i < size; i++)
            data[i] = input[i].cast<double>();
        Matrix m(1, size);
        for (int i = 0; i < size; i++)
            m.data[0][i] = data[i];
        double result = net.forward(m).data[0][0];
        delete[] data;
        return result;
            })
        .def("train", [](Network& net, py::list input, double expected, double lr) {
        int size = (int)input.size();
        double* data = new double[size];
        for (int i = 0; i < size; i++)
            data[i] = input[i].cast<double>();
        Matrix m(1, size);
        for (int i = 0; i < input.size(); i++)
            m.data[0][i] = data[i];
        net.train(m, expected, lr);
        delete[] data;
            })
        .def("mse", &Network::mse)
        .def("save", &Network::save)
        .def("load", &Network::load);
}