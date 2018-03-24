#include <iostream>
#include "NeuralNetwork.h"

int main() {
    char* path = "/home/peter/CLionProjects/LeanNNs/NN 1";
    NeuralNetwork *neuralNetwork = new NeuralNetwork({1, 3, 1});
    neuralNetwork->PrintWeights();
    printf("\n");
    NeuralNetwork::WriteToFile(*neuralNetwork, path);

    NeuralNetwork *neuralNetwork2 = NeuralNetwork::ReadFromFile(path);
    neuralNetwork2->PrintWeights();

    // srand(time(NULL))
    return 0;
}