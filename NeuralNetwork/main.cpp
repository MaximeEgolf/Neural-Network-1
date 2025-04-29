#include <iostream>

#include "Layer.h"
#include "Utils.h"

int main()
{
    // Random Seed
    srand(time(NULL));

    // Initialisation
    float* inputs = new float[4];
    inputs[0] = 0.12;
    inputs[1] = -0.51;
    inputs[2] = 0.37;
    inputs[3] = -0.20;

    Utils::Print1D(inputs, 4, "Inputs");

    Layer layer1 = Layer(4, 2);
    layer1.PrintWeights();
    layer1.PrintBias();
    float* outputs = layer1.CalculateOutputs(inputs);

    Utils::Print1D(outputs, 2, "Outputs");
}