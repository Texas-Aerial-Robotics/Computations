//
// Created by peter on 1/24/18.
//

#include <cstdlib>
#include <stdio.h>
#include <string.h> // For memcpy
#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(std::vector<int32_t> topology) {
    this->topology = topology;

    // Allocate neurons vector:
    neurons.resize(topology.size());

    // Allocate weights.
    NeuralNetwork::AllocWeights(topology, weights);

    // Initialize neurons vector:
    for (int32_t i = 0; i < topology.size() - 1; i++) { // Current layer
        neurons[i] = std::vector <float>(topology[i]);

        for (int32_t j = 0; j < topology[i]; j++) { // Current layer, current neuron
            for (int32_t k = 0; k < topology[i+1]; k++) { // Next layer, current neuron
                weights[i][j][k] = RandRange (minInitWeight, maxInitWeight);
            }
        }
    }

    int32_t outputCount = topology [topology.size() - 1];
    neurons[topology.size() - 1] = std::vector<float>(outputCount);
}

// Assumes given weights is independent of other NNs.
NeuralNetwork::NeuralNetwork(std::vector<int32_t> topology, std::vector<std::vector<std::vector<float>>> weights) {
    this->topology = topology;
    this->weights = weights;

    // Resize neurons before assigning stuff to them!
    neurons.resize(topology.size());
    for (int32_t i = 0; i < topology.size() - 1; i++) { // Current layer
        neurons[i] = std::vector <float>(topology[i]);
    }

    int32_t outputCount = topology [topology.size() - 1];
    neurons[topology.size() - 1] = std::vector<float>(outputCount);
}

// The following method probably uses a lot of stack memory. I didn't want to bother with malloc and pointer arithmetic.
NeuralNetwork NeuralNetwork::DeepCopy(NeuralNetwork nnToCopy) {
    std::vector<int32_t> topology;

    for (int32_t i = 0; i < nnToCopy.topology.size(); i++) {
        topology[i] = nnToCopy.topology[i];
    }

    // Just deep copy weights: neurons and output are essentially temp variables:
    std::vector<std::vector<std::vector<float>>> weights;

    for (int32_t i = 0; i < nnToCopy.weights.size(); i++) { // Current layer
        for (int32_t j = 0; j < nnToCopy.weights[i].size(); j++) { // Current layer, current neuron
            for (int32_t k = 0; k < nnToCopy.weights[i][j].size(); k++) { // Next layer, current neuron
                weights[i][j][k] = nnToCopy.weights[i][j][k];
            }
        }
    }

    return NeuralNetwork (topology, weights);
}

NeuralNetwork* NeuralNetwork::ReadFromFile(char *path) {
    // fopen at path
    FILE* nnFile = fopen (path, "r");

    // Read topology

    // First read topology length (# of layers).
    char temp [4];
    ReadCharsFromFile (temp, 4, nnFile);
    uint32_t nnLayerCount = (uint32_t) *temp;
    memcpy(&temp, &(nnLayerCount), 4); // temp has topology length now. 4 bytes for a uint32_t.

    std::vector<int32_t> topology (nnLayerCount);

    // Now read each layer's neuron count.
    for (uint32_t i = 0; i < nnLayerCount; i++) {
        ReadCharsFromFile(temp, 4, nnFile);
        memcpy(&(topology[i]), temp, 4);
    }

    // Allocate space for weights.
    std::vector<std::vector<std::vector<float>>> weights;
    AllocWeights(topology, weights);
    
    // Read all weights
    for (int32_t i = 0; i < nnLayerCount - 1; i++) { // Current layer
        for (int32_t j = 0; j < topology[i]; j++) { // Current layer, current neuron
            for (int32_t k = 0; k < topology[i + 1]; k++) { // Next layer, current neuron
                ReadCharsFromFile(temp, 4, nnFile);
                memcpy(&(weights[i][j][k]), temp, 4);
            }
        }
    }

    // fclose b/c that's good.
    fclose(nnFile);

    // Return new NN w/ given topology and weights.
    return new NeuralNetwork (topology, weights);
}

void NeuralNetwork::WriteToFile(NeuralNetwork nn, char *path) {
    // fopen at path
    FILE* nnFile = fopen (path, "w");

    // Write topology
    // First write topology length (# of layers).
    char temp [4];
    uint32_t nnLength = nn.topology.size();
    memcpy(&temp, &(nnLength), 4); // temp has topology length now. 4 bytes for a uint32_t.
    WriteCharsToFile(temp, 4, nnFile);

    // Now write each layer's neuron count.
    for (uint32_t i = 0; i < nn.topology.size(); i++) {
        memcpy(&temp, &(nn.topology[i]), 4);
        WriteCharsToFile(temp, 4, nnFile);
    }


    // Write all weights
    for (int32_t i = 0; i < nn.weights.size(); i++) { // Current layer
        for (int32_t j = 0; j < nn.weights[i].size(); j++) { // Current layer, current neuron
            for (int32_t k = 0; k < nn.weights[i][j].size(); k++) { // Next layer, current neuron
                memcpy(&temp, &(nn.weights[i][j][k]), 4);
                WriteCharsToFile(temp, 4, nnFile);
            }
        }
    }

    // fclose b/c that's good.
    fclose(nnFile);

    // Done!
}

// Note: to get output length, just get NeuralNetwork's topology[layerCount - 1]!
std::vector<float> NeuralNetwork::FeedForward(std::vector<float> input) {
    // Pass inputs to NN input layer.
    for (int32_t i = 0; i < topology[0]; i++) {
        neurons[0][i] = input[i];
    }

    // Propagate input through NN.
    for (int32_t i = 0; i < weights.size(); i++) { // Current layer
        for (int32_t j = 0; j < weights[i].size(); j++) { // Current layer, current neuron
            for (int32_t k = 0; k < weights[i][j].size(); k++) { // Next layer, current neuron
                neurons[i + 1][k] += neurons[i][j] * weights[i][j][k];
            }
        }
    }

    return neurons[topology.size() - 1];
}

void NeuralNetwork::Mutate() {
    for (int32_t i = 0; i < weights.size(); i++) { // Current layer
        for (int32_t j = 0; j < weights[i].size(); j++) { // Current layer, current neuron
            for (int32_t k = 0; k < weights[i][j].size(); k++) { // Next layer, current neuron
                weights[i][j][k] = MutateWeight(weights[i][j][k]);
            }
        }
    }
}

// Helper functions:

// Allocates weights given a topology.
void NeuralNetwork::AllocWeights (std::vector<int32_t> topology, std::vector<std::vector<std::vector<float>>> &weights) {
    weights.resize(topology.size() - 1); // Use resize instead of reserve b/c reserve doesn't really allocate array space.

    for (int32_t i = 0; i < topology.size() - 1; i++) { // Current layer
        weights[i].resize ((topology[i]));

        for (int32_t j = 0; j < topology[i]; j++) { // Current layer, current neuron
            weights[i][j].resize (topology[i + 1]);
        }
    }
}

// Returns a mutated version of the given weight value
float NeuralNetwork::MutateWeight(float weight) {
    if (RandRange(0, 1) < weightMutChance) {
        // Flip sign, add, or multiply weight.

    }
}

float NeuralNetwork::ActivationFunction(float input) {
    return input / (1 + Abs(input));
}

// Returns a random float value b/w minVal and maxVal.
float NeuralNetwork::RandRange (float minVal, float maxVal) {
    return minVal + (maxVal - minVal) * ((float) rand() / (float) RAND_MAX);
}

float NeuralNetwork::Abs (float input) {
    if (input < 0) return -input;
    else return input;
}

void NeuralNetwork::WriteCharsToFile(char *chars, uint32_t length, FILE *fileStream) {
    for (uint32_t i = 0; i < length; i++) {
        fputc(chars[i], fileStream);
    }
}

void NeuralNetwork::ReadCharsFromFile(char* chars, uint32_t length, FILE *fileStream) {
    for (uint32_t i = 0; i < length; i++) {
        chars[i] = fgetc(fileStream);
    }
}

void NeuralNetwork::PrintWeights() {
    for (uint32_t i = 0; i < weights.size(); i++) {
        for (int32_t j = 0; j < weights[i].size(); j++) { // Current layer, current neuron
            for (int32_t k = 0; k < weights[i][j].size(); k++) { // Next layer, current neuron
                printf("%g\n", weights[i][j][k]);
            }
        }
    }
}