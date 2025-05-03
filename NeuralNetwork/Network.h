#pragma once
#include "Layer.h"

class Network
{
private:
	int numberOfLayers;
	float loss;
	float* output;
	Layer** layers;

public:
	Network(std::initializer_list<int> nums);
	~Network();
	float CalculateLoss(float* expectedOutputs);
	void CalculateOutputs(float* inputs);
	void PrintNetwork();
};

