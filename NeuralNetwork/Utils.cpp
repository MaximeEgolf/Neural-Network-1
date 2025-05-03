#include "Utils.h"

void Utils::Print1D(float* inputs1D, int bounds, std::string message)
{
	// Header
	std::cout << "---\t" << message << "\t---" << std::endl;

	// Print
	std::cout << "{";
	for (int i = 0; i < bounds; i++) 
	{
		std::cout << " " << inputs1D[i] << " ";
	}
	std::cout << "}" << std::endl;
}

void Utils::Print2D(float** inputs2D, int boundsROW, int boundsCOL, std::string message)
{
	// Header
	std::cout << "---\t" << message << "\t---" << std::endl;

	// Print
	std::cout << "{" << std::endl;
	for (int i = 0; i < boundsROW; i++) {
		std::cout << "{";
		for (int j = 0; j < boundsCOL; j++) {
			std::cout << " " << inputs2D[i][j] << " ";
		}

		std::cout << "}," << std::endl;
	}
	std::cout << "}" << std::endl;
}

void Utils::PrintMNISTImage(float* mnistImage, int imageSize, int boundsROW)
{
	for (int i = 0; i < imageSize; i++) {
		if (i != 0 && i % boundsROW == 0)
			std::cout << std::endl;

		std::cout << (mnistImage[i] > 0.50f ? "#" : " ");
	}
	std::cout << std::endl;
}

float Utils::GenerateFraction(float minBounds, float maxBounds) {
	float random = (float)rand() / RAND_MAX;
	return (minBounds + random * (maxBounds - minBounds));
}
