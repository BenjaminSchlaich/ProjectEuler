#ifndef NEURALNET_H
#define NEURALNET_H

#include <vector>
#include <cmath>
#include <random>

namespace nnet
{
	constexpr double e_Constant = 2.718281828459045;

	using std::vector;

	class Layer;
	class NeuralNet;

	class Layer
	{
	public:
		Layer(vector<double> *in, int neurons, NeuralNet *nn);

		vector<double> *activation();	// (output)

		inline void setInput(vector<double> *in)
		{
			if (in->size() != this->in->size())
			{
				return;
			}

			this->in = in;
		}

		void propagate();				// propagete <in> to <a>

	private:
		NeuralNet *nn;		// this way we only need one random generator class
		vector<double> *in;	// input
		vector<double> w;	// weights
		vector<double> b;	//biases
		vector<double> a;	// activation (i.e. output)
	};

	class NeuralNet
	{
	public:
		NeuralNet(vector<double> *in, vector<int> layers);

		inline double rand()
		{
			return distr(randGenerator);
		}

		inline bool setInput(vector<double> *v)
		{
			if (v->size() != in->size())
				return false;

			in = v;
		}

		inline vector<double> *propagate()
		{
			layer[0].setInput(in);
			for (Layer l : layer)
				l.propagate();

			return layer.back().activation();
		}

	private:
		static std::mt19937_64 randGenerator;
		static std::uniform_real_distribution<> distr;
		
		vector<double> *in;
		vector<Layer> layer;
	};

} // namespace nnet

#endif //NEURALNET_H