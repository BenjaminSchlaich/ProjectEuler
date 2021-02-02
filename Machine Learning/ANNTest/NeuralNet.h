#pragma once

#include <vector>
#include <random>
#include <cmath>

namespace nnet
{
	typedef unsigned int u_int;

	using std::vector;

	constexpr double e_Constant = 2.718281828459045;

	class NeuralNet;
	class Layer;

	

	class NeuralNet
	{
	public:

		NeuralNet(int inputs, vector<int> layers, int outputs, double learningRate = 1.0);

		void propagate(vector<double> input);
		void backprop(vector<double> desired);

		vector<double> getOutput();

		inline static double rand()
		{
			return urd(mersenneTwister);
		}

	private:

		static std::mt19937_64 mersenneTwister;
		static std::uniform_real_distribution<double> urd;

		double learningRate;

		vector<double> input;
		vector<Layer> layer;
		vector<double> output;
	};

	class Layer
	{
		friend void NeuralNet::backprop(vector<double> desired);

	public:

		inline Layer()
		{

		}

		Layer(int inputs, int neurons);

		inline int size()
		{
			return bias.size();
		}

		void propagate(vector<double> input);
		void backprop(Layer lNext);

		inline vector<double> output()
		{
			return activation;
		}

	private:
		vector<double> weight;
		vector<double> bias;
		vector<double> activation;
		vector<double> deltas;
	};

} // namespace nnet