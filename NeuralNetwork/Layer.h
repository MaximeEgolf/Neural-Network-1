#pragma once
#include <iostream>
#include "Utils.h"

class Layer
{
private:
	float** weights;
	float* biases;

	int neuronsIn, neuronsOut;

public:
	Layer(int nIn, int nOut);
	~Layer();
	float* CalculateOutputs(float* inputs);
	void PrintWeights();
	void PrintBias();
};

