#include "Layer.h"

Layer::Layer(int nIn, int nOut) {
	
	neuronsIn = nIn;
	neuronsOut = nOut;

	// Weights
	weights = new float*[neuronsOut];
	for (int i = 0; i < neuronsOut; i++) {
		weights[i] = new float[neuronsIn];
	}

	// Biases
	biases = new float[neuronsOut];

	// Outputs
	outputs = new float[neuronsOut]();

	// Initial
	for (int i = 0; i < neuronsOut; i++) {
		for (int j = 0; j < neuronsIn; j++) {
			weights[i][j] = Utils::GenerateFraction(-1.0f, 1.0f);
		}

		biases[i] = Utils::GenerateFraction(-1.0f, 1.0f);
	}
}

Layer::~Layer()
{
	// Weights
	for (int i = 0; i < neuronsOut; i++) {
		delete[] weights[i];
	}
	delete[] weights;

	// Biases
	delete[] biases;

	// Outputs
	delete[] outputs;
}

float Layer::ActivationReLU(float weightedInput) {
	if (weightedInput > 0)
		return weightedInput;
	else
		return 0;
}

float Layer::ActivationSigmoid(float weightedInput) {
	return 1 / (1 + exp(-weightedInput));
}

float* Layer::CalculateOutputs(float* inputs)
{
	std::fill(outputs, outputs + neuronsOut, 0.0f);

	for (int i = 0; i < neuronsOut; i++) {
		outputs[i] += biases[i];

		for (int j = 0; j < neuronsIn; j++) {
			outputs[i] += inputs[j] * weights[i][j];
		}

		outputs[i] = ActivationSigmoid(outputs[i]);
	}

	return outputs;
}

void Layer::PrintWeights()
{
	Utils::Print2D(weights, neuronsOut, neuronsIn, "Weights");
}

void Layer::PrintBiases()
{
	Utils::Print1D(biases, neuronsOut, "Biases");
}

void Layer::PrintOutputs()
{
	Utils::Print1D(outputs, neuronsOut, "Outputs");
}
