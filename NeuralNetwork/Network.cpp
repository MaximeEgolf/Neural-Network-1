#include "Network.h"

Network::Network(std::initializer_list<int> nodes) {
	const int* nodesPtr = nodes.begin();
	numberOfLayers = nodes.size() - 1;

	// Layers
	layers = new Layer*[numberOfLayers];

	for (int i = 0; i < numberOfLayers; i++) {
		int inputSize = *nodesPtr++;
		int outputSize = *nodesPtr;

		layers[i] = new Layer(inputSize, outputSize);
	}

	loss = 0;
	output = nullptr;
}

Network::~Network(){
	// Layers
	for (int i = 0; i < numberOfLayers; i++) {
		delete layers[i];
	}

	delete[] layers;
}

float Network::CalculateLoss(float* expectedOutputs) {
	// Loss is only the last layer
	Layer* outputLayer = layers[numberOfLayers];
	return outputLayer->CalculateLoss(expectedOutputs);
}

void Network::CalculateOutputs(float* inputs) {
	for (int i = 0; i < numberOfLayers; i++) {
		inputs = layers[i]->CalculateOutputs(inputs);
	}

	output = inputs;
}


void Network::PrintNetwork() {
	for (int i = 0; i < numberOfLayers; i++) {
		std::cout << "----------" << "LAYER " << i << "----------" << std::endl;
		layers[i]->PrintWeights();
		layers[i]->PrintBiases();
		layers[i]->PrintOutputs();
		std::cout << "------" << "END OF LAYER " << i << "------" << std::endl;
	}
}