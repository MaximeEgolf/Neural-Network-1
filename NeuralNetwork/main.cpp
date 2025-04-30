#include <iostream>

#include "Layer.h"
#include "Utils.h"
#include "Network.h"

int main()
{
    // Random Seed
    srand(time(NULL));

    // Initialisation
    float* inputs = new float[4];
    inputs[0] = 0.12f;
    inputs[1] = -0.51f;
    inputs[2] = 0.37f;
    inputs[3] = -0.20f;

    Network network = Network({ 4,2,3,4 });
    float* output = network.CalculateOutputs(inputs);
    network.PrintNetwork();
}