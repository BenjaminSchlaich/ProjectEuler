#include "NeuralNet.h"

using namespace nnet;

std::mt19937_64 NeuralNet::mersenneTwister = std::mt19937_64(std::random_device()());

std::uniform_real_distribution<> NeuralNet::urd = std::uniform_real_distribution<double>(0.0, 1.0);

double sigmoid(double d)
{
	return 1 / (std::pow(e_Constant, -d) + 1);
}

vector<double> cost(vector<double> output, vector<double> desired)
{
	for (int i = 0; i < output.size(); i++)
		output[i] = (output[i] - desired[i]) * (output[i] - desired[i]);

	return output;
}

Layer::Layer(int inputs, int neurons)
{
	weight = vector<double>(neurons * inputs);
	bias = vector<double>(neurons);
	activation = vector<double>(neurons);
	deltas = vector<double>(neurons*inputs);

	for (u_int i = 0; i < weight.size(); i++)
	{
		weight[i] = NeuralNet::rand();
		deltas[i] = 0.0;
	}

	for (int i = 0; i < neurons; i++)
	{
		bias[i] = NeuralNet::rand();
		activation[i] = 0.0;
	}
}

void Layer::propagate(vector<double> input)
{
	for (u_int x = 0; x < bias.size(); x++)
	{
		double d=0;
		for (u_int y = 0; y < input.size(); y++)
		{
			d += weight.at(x * input.size() + y) * input.at(y);
		}

		activation[x] = sigmoid(d - bias[x]);
	}
}

void Layer::backprop(Layer lNext)
{
	vector<double> deltas(activation.size());
	for (int x = 0; x < activation.size(); x++)
	{
		double delta = 0;
		for (int y = 0; y < lNext.activation.size(); y++)
		{
			delta += lNext.deltas[y] * lNext.weight[activation.size() * x + y];
		}
		delta *= activation[x] * (1 - activation[x]);
		deltas[x] = delta;
	}
}

NeuralNet::NeuralNet(int inputs, vector<int> hidden_layers, int outputs, double learningRate)
{
	input = vector<double>(inputs);
	layer = vector<Layer>(hidden_layers.size()+2);
	output = vector<double>(outputs);

	layer[0] = Layer(inputs, inputs);
	for (u_int i = 1; i < layer.size()-1; i++)
	{
		layer[i] = Layer(layer[i - 1].size(), hidden_layers[i - 1]);
	}
	layer[layer.size() - 1] = Layer(layer[layer.size() - 2].size(), outputs);

	this->learningRate = learningRate;
}

void nnet::NeuralNet::propagate(vector<double> input)
{
	layer[0].propagate(input);
	for (u_int i = 1; i < layer.size(); i++)
		layer[i].propagate(layer[i-1].output());

	output = layer.back().output();

}

void nnet::NeuralNet::backprop(vector<double> desired)
{
	Layer& l = layer.back();
	for (int i = 0; i < l.size(); i++)
	{
		l.activation[i] = (l.activation[i] - desired[i]) * l.activation[i] * (1 - l.activation[i]);
	}

	for (int i = layer.size() - 2; i >= 0; i--)
		layer[i].backprop(layer[i + 1]);

	for (int x = 0; x < layer[0].activation.size(); x++)
	{
		for (int y = 0; y < layer[0].activation.size(); y++)
		{
			layer[0].weight[x * layer[0].activation.size() + y] -= learningRate * layer[0].deltas[x];
		}
	}

	for (int l = 1; l < layer.size(); l++)
	{
		for (int n = 0; n < layer[l].size(); n++)
		{
			for (int w = 0; w < layer[l - 1].size(); w++)
			{
				layer[l].weight[n * layer[l - 1].size() + w] -= learningRate * layer[l].deltas[n];
			}
		}
	}
}

vector<double> nnet::NeuralNet::getOutput()
{
	return output;
}
