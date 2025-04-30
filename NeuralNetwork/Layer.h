#pragma once
#include <iostream>
#include "Utils.h"

class Layer
{
private:
	int neuronsIn, neuronsOut;

	float** weights;
	float* biases;
	float* outputs;

public:
	Layer(int nIn, int nOut);
	~Layer();
	float ActivationReLU(float weightedInput);
	float ActivationSigmoid(float weightedInput);
	float* CalculateOutputs(float* inputs);
	void PrintWeights();
	void PrintBiases();
	void PrintOutputs();
};

