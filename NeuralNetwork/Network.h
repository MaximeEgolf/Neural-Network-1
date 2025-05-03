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
	void CalculateLoss(float* expectedOutputs);
	void CalculateOutputs(float* inputs);
	void PrintNetwork(bool pWeights = true, 
					  bool pBias = true, 
					  bool pOutputs = true, 
					  bool pLoss = true);
};

