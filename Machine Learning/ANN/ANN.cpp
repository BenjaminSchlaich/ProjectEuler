// ANN.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <vector>
#include "NeuralNet.h"

using namespace nnet;

int main()
{
    std::cout << "Hello World!\n";
    auto v = std::vector<int>(3);
    v[0] = 3;
    v[1] = 3;
    v[2] = 2;
    std::vector<double> input{ 11.2,56.3,0.33 };
    NeuralNet ann(&input, v);

    ann.setInput(&input);
    auto output = ann.propagate();

    for (double d : *output)
        std::cout << d << std::endl;

    input = { 44.0, 22.1, 12.6 };
    ann.setInput(&input);
    output = ann.propagate();
    for (double d : *output)
        std::cout << d << std::endl;
}
