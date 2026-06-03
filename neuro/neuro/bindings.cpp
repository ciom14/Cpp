#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "network.h"

namespace py = pybind11;

PYBIND11_MODULE(neuro, m) {
    py::class_<Network>(m, "Network")
        .def(py::init<std::vector<int>, int>())
        .def("forward", [](Network& net, std::vector<double> input) {
        Matrix m(1, input.size());
        for (int i = 0; i < input.size(); i++)
            m.data[0][i] = input[i];
        return net.forward(m).data[0][0];
            })
        .def("train", [](Network& net, std::vector<double> input, double expected, double lr) {
        Matrix m(1, input.size());
        for (int i = 0; i < input.size(); i++)
            m.data[0][i] = input[i];
        net.train(m, expected, lr);
            })
        .def("mse", &Network::mse)
        .def("save", &Network::save)
        .def("load", &Network::load);
}