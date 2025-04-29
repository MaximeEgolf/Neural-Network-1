#include "Layer.h"

Layer::Layer(int nIn, int nOut) {
	
	neuronsIn = nIn;
	neuronsOut = nOut;

	// Initialization (weights)
	weights = new float*[neuronsOut];
	for (int i = 0; i < neuronsOut; i++) {
		weights[i] = new float[neuronsIn];
	}

	// Initialization (bias)
	biases = new float[neuronsOut];

	// Initial Values
	for (int i = 0; i < neuronsOut; i++) {
		for (int j = 0; j < neuronsIn; j++) {
			weights[i][j] = (float)(rand()) / (float)(RAND_MAX);
		}

		biases[i] = (float)(rand()) / (float)(RAND_MAX);
	}
}

Layer::~Layer()
{
	// Destruction (weights)
	for (int i = 0; i < neuronsOut; i++) {
		delete[] weights[i];
	}
	delete[] weights;

	// Destruction (bias)
	delete[] biases;
}

// Return: Each neuron has an output that depends on the input
float* Layer::CalculateOutputs(float* inputs)
{
	float* outputs = new float[neuronsOut]();

	for (int i = 0; i < neuronsOut; i++) {
		for (int j = 0; j < neuronsIn; j++) {
			outputs[i] += inputs[j] * weights[i][j];
		}

		outputs[i] += biases[i];
	}

	return outputs;
}

void Layer::PrintWeights()
{
	Utils::Print2D(weights, neuronsOut, neuronsIn, "Weights");
}

void Layer::PrintBias()
{
	Utils::Print1D(biases, neuronsOut, "Biases");
}