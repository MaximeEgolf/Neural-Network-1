#include <iostream>
#include <fstream>

#include "Layer.h"
#include "Utils.h"
#include "Network.h"

unsigned char** ReadMNISTImages(std::string fullPath, int& numberOfImages, int& imageSize) {

    auto reverseInt = [](int i) {
        unsigned char c1, c2, c3, c4;
        c1 = i & 255, c2 = (i >> 8) & 255, c3 = (i >> 16) & 255, c4 = (i >> 24) & 255;
        return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
        };

    std::ifstream file(fullPath, std::ios::binary);

    if (file.is_open()) {
        int magicNumber = 0, nRows = 0, nCols = 0;

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

        imageSize = nRows * nCols;

        unsigned char** _dataset = new unsigned char* [numberOfImages];
        for (int i = 0; i < numberOfImages; i++) {
            _dataset[i] = new unsigned char[imageSize];
            file.read((char*)_dataset[i], imageSize);
        }

        return _dataset;
    }
    else {
        throw std::runtime_error("Cannot open file `" + fullPath + "`!");
    }
}

unsigned char* ReadMNISTLabels(std::string fullPath, int& numberOfLabels) {
    auto reverseInt = [](int i) {
        unsigned char c1, c2, c3, c4;
        c1 = i & 255, c2 = (i >> 8) & 255, c3 = (i >> 16) & 255, c4 = (i >> 24) & 255;
        return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
        };

    std::ifstream file(fullPath, std::ios::binary);

    if (file.is_open()) {
        int magic_number = 0;
        file.read((char*)&magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);

        if (magic_number != 2049) 
            throw std::runtime_error("Invalid MNIST label file!");

        file.read((char*)&numberOfLabels, sizeof(numberOfLabels)), numberOfLabels = reverseInt(numberOfLabels);

        unsigned char* _dataset = new unsigned char[numberOfLabels];
        for (int i = 0; i < numberOfLabels; i++) {
            file.read((char*)&_dataset[i], 1);
        }
        return _dataset;
    }
    else {
        throw std::runtime_error("Unable to open file `" + fullPath + "`!");
    }
}

void FreeMNIST(unsigned char* labels, unsigned char** images, int numberOfImages) {
    // Labels
    delete[] labels;
    
    // Images
    for (int i = 0; i < numberOfImages; ++i) {
        delete[] images[i];
    }
    delete[] images;
}

int main() {
    // Random Seed
    srand(time(NULL));

    // MNIST (allocate)
    int imageSize, numberOfImages, numberOfLabels;
    unsigned char** images = ReadMNISTImages("../MNIST/training/train-images.idx3-ubyte", numberOfImages, imageSize);
    unsigned char* labels = ReadMNISTLabels("../MNIST/training/train-labels.idx1-ubyte", numberOfLabels);

    for (int i = 0; i < 10; i++) {
        Utils::PrintMNISTImage(images[i], imageSize, 28);
        std::cout << "--- \t Label = " << (int)labels[i] << "\t ---" << std::endl;
    }
    // Neural Network
    /*
    Network network = Network({ 4,2,3,4 });
    network.CalculateOutputs(inputs);
    network.PrintNetwork();
    */

    // MNIST (free)
    FreeMNIST(labels, images, numberOfImages);
}