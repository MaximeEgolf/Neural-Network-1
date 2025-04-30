#pragma once
#include "Layer.h"

class Network
{
private:
	int numberOfLayers;
	Layer** layers;

public:
	Network(std::initializer_list<int> nums);
	~Network();
	float* CalculateOutputs(float* inputs);
	void PrintNetwork();
};

