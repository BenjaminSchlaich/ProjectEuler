// ANNTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "NeuralNet.h"

using namespace std;

int main()
{
    std::vector<int> h{ 3,2 };
    nnet::NeuralNet xor_ann(2,h,1);
    std::vector<double> v0 = { 0.0,0.0 };
    std::vector<double> v1 = { 1.0,0.0 };
    std::vector<double> v2 = { 0.0,1.0 };
    std::vector<double> v3 = { 1.0,1.0 };

    xor_ann.propagate(v0);
    vector<double> o = xor_ann.getOutput();
    cout << o[0] << endl;

    xor_ann.propagate(v1);
    o = xor_ann.getOutput();
    cout << o[0] << endl;

    xor_ann.propagate(v2);
    o = xor_ann.getOutput();
    cout << o[0] << endl;

    xor_ann.propagate(v3);
    o = xor_ann.getOutput();
    cout << o[0] << endl;

    for (int i = 0; i < 100; i++)
    {
        xor_ann.propagate(v0);
        xor_ann.backprop({ 0.0 });
        xor_ann.propagate(v1);
        xor_ann.backprop({ 1.0 });
        xor_ann.propagate(v2);
        xor_ann.backprop({ 1.0 });
        xor_ann.propagate(v3);
        xor_ann.backprop({ 0.0 });
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
