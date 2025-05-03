#include <iostream>
#include <fstream>

#include "Layer.h"
#include "Utils.h"
#include "Network.h"

constexpr int OUTPUTS = 10;

static float** ReadMNISTImages(std::string fullPath, int& numberOfImages, int& nCols, int& nRows) {

    auto reverseInt = [](int i) {
        unsigned char c1, c2, c3, c4;
        c1 = i & 255, c2 = (i >> 8) & 255, c3 = (i >> 16) & 255, c4 = (i >> 24) & 255;
        return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
        };

    std::ifstream file(fullPath, std::ios::binary);

    if (file.is_open()) {
        int magicNumber = 0;

        // Magic Number
        file.read((char*)&magicNumber, sizeof(magicNumber));
        magicNumber = reverseInt(magicNumber);

        if (magicNumber != 2051) 
            throw std::runtime_error("Invalid MNIST image file!");

        // Number of images
        file.read((char*)&numberOfImages, sizeof(numberOfImages));
        numberOfImages = reverseInt(numberOfImages);

        // Rows
        file.read((char*)&nRows, sizeof(nRows));
        nRows = reverseInt(nRows);

        // Columns
        file.read((char*)&nCols, sizeof(nCols));
        nCols = reverseInt(nCols);

        int imageSize = nRows * nCols;

        float** dataset = new float*[numberOfImages];
        unsigned char* buffer = new unsigned char[imageSize];

        for (int i = 0; i < numberOfImages; i++) {
            file.read((char*)buffer, imageSize);
            dataset[i] = new float[imageSize];

            for (int j = 0; j < imageSize; j++) {
                dataset[i][j] = buffer[j] / 255.0f;
            }
        }

        delete[] buffer;

        return dataset;
    }
    else {
        throw std::runtime_error("Cannot open file `" + fullPath + "`!");
    }
}

static float** ReadMNISTLabels(std::string fullPath, int& numberOfLabels) {
    auto reverseInt = [](int i) {
        unsigned char c1, c2, c3, c4;
        c1 = i & 255, c2 = (i >> 8) & 255, c3 = (i >> 16) & 255, c4 = (i >> 24) & 255;
        return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
        };

    std::ifstream file(fullPath, std::ios::binary);

    if (file.is_open()) {
        int magicNumber = 0;
        file.read((char*)&magicNumber, sizeof(magicNumber));
        magicNumber = reverseInt(magicNumber);

        if (magicNumber != 2049) 
            throw std::runtime_error("Invalid MNIST label file!");

        file.read((char*)&numberOfLabels, sizeof(numberOfLabels)), numberOfLabels = reverseInt(numberOfLabels);

        float** dataset = new float*[numberOfLabels];
        unsigned char buffer;

        for (int i = 0; i < numberOfLabels; i++) {
            file.read((char*)&buffer, 1);
            
            // One hot encoding
            dataset[i] = new float[OUTPUTS]();
            dataset[i][buffer] = 1.0f;
        }
        return dataset;
    }
    else {
        throw std::runtime_error("Unable to open file `" + fullPath + "`!");
    }
}

static void FreeMNIST(float** elements, int numberOfElements) {
    for (int i = 0; i < numberOfElements; ++i) {
        delete[] elements[i];
    }
    delete[] elements;
}

int main() {
    // Random Seed
    srand(time(NULL));

    // MNIST (allocate)
    int nColsImage, nRowsImage, numberOfImages, numberOfLabels;

    float** images = ReadMNISTImages("../MNIST/training/train-images.idx3-ubyte", numberOfImages, nColsImage, nRowsImage);
    float** labels = ReadMNISTLabels("../MNIST/training/train-labels.idx1-ubyte", numberOfLabels);

    // Neural Network
    Network network = Network({ nColsImage * nRowsImage, 5, OUTPUTS });

    for (int i = 0; i < 10; i++) {
        Utils::PrintMNISTImage(images[i], nColsImage * nRowsImage, nColsImage);
        Utils::Print1D(labels[i], OUTPUTS, "Label");
        network.CalculateOutputs(images[i]);
        network.CalculateLoss(labels[i]);
        network.PrintNetwork(false, false, true, true);
    }

    // MNIST (free)
    FreeMNIST(images, numberOfImages);
    FreeMNIST(labels, numberOfLabels);
}