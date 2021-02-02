#include "NeuralNet.h"

using namespace nnet;

double sigmoid(double d)
{
	return 1 / (std::pow(e_Constant, -d) + 1);
}

Layer::Layer(vector<double> *in, int neurons, NeuralNet* nn)
{
	this->nn = nn;
	this->in = in;
	w = vector<double>(in->size() * neurons);
	b = vector<double>(neurons);
	a = vector<double>(neurons);

	for (int i = 0; i < static_cast<int>(w.size()); i++)
		w[i] = nn->rand();

	for (int i = 0; i < static_cast<int>(b.size()); i++)
	{
		b[i] = nn->rand();
		a[i] = 0;
	}
}

vector<double> *Layer::activation()
{
	return &a;
}

void Layer::propagate()
{
	for (int x = 0; x < static_cast<int>(a.size()); x++)	// iterate through neurons
	{
		double d = 0;	// this will hold the new activation
		for (int y = 0; y < static_cast<int>(in->size()); y++)	// iterate through inputs
		{
			double weight = w.at(in->size() * x + y);
			double input = in->at(y);
			d += weight*input;
		}

		d -= b[x];
		a[x] = sigmoid(d);
	}
}

std::mt19937_64 NeuralNet::randGenerator;
std::uniform_real_distribution<> NeuralNet::distr;


NeuralNet::NeuralNet(vector<double> *in, vector<int> layers)
{
	this->in = in;
	layer = vector<Layer>();
	layer.push_back(Layer(in, in->size(), this));
	Layer *prevL = &(*layer.begin());
	for (int i = 1; i < static_cast<int>(layers.size()); i++)
	{
		layer.push_back(Layer(prevL->activation(), layers[i], this));
		prevL = &(layer.back());
	}

}