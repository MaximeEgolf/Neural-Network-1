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

void Network::CalculateLoss(float* expectedOutputs) {
	// Loss is only the last layer
	Layer* outputLayer = layers[numberOfLayers - 1];
	loss = outputLayer->CalculateLoss(expectedOutputs);
}

void Network::CalculateOutputs(float* inputs) {
	for (int i = 0; i < numberOfLayers; i++) {
		inputs = layers[i]->CalculateOutputs(inputs);
	}

	output = inputs;
}


void Network::PrintNetwork(bool pWeights, bool pBias, bool pOutputs, bool pLoss) {
	std::cout << "---\t" << "Neural Network " << "\t---" << std::endl;
	for (int i = 0; i < numberOfLayers; i++) {
		std::cout << "---\t" << "Layer " << i << "\t---" << std::endl;
		if (pWeights == true)
			layers[i]->PrintWeights();
		if (pBias == true)
			layers[i]->PrintBiases();
		if (pOutputs == true)
			layers[i]->PrintOutputs();
		std::cout << std::endl;
	}

	if (pLoss == true)
		std::cout << "Loss : " << loss << std::endl;

	std::cout << std::endl;
}