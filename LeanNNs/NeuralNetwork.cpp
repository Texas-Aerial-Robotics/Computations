//
// Created by peter on 1/24/18.
//

#include <cstdlib>
#include "NeuralNetwork.h"

// TODO: Implement activation and weight mutation functions.
// TODO: NN Constructors



NeuralNetwork::NeuralNetwork(std::vector<int32_t> topology) {
    this->topology = topology;
    // Create neurons vector, output vector
    neurons = std::vector <std::vector<float>> (topology.size());
    weights = std::vector <std::vector<std::vector<float>>> (topology.size());

    // Initialize neurons, weights, and output vectors.
    for (int32_t i = 0; i < topology.size() - 1; i++) { // Current layer
        neurons[i] = std::vector <float>(topology[i]);
        weights[i] = std::vector <std::vector<float>>(topology[i]);

        for (int32_t j = 0; j < topology[i]; j++) { // Current layer, current neuron
            weights[i][j] = std::vector<float>(topology[i + 1]);

            for (int32_t k = 0; k < topology[i+1]; k++) { // Next layer, current neuron
                weights[i][j][k] = rand; // TODO: implement method for random float vals.
            }
        }
    }

    int32_t outputCount = topology [topology.size() - 1];

    neurons[topology.size() - 1] = std::vector<float>(outputCount);
}

NeuralNetwork NeuralNetwork::DeepCopy(NeuralNetwork nnToCopy) {
    std::vector<int32_t > topology;

    for (int32_t i = 0; i < topology.size(); i++) {
        topology[i] = nnToCopy.topology[i];
    }

    // Just deep copy weights: neurons and output are essentially temp variables:
    std::vector<std::vector<std::vector<float>>> weights;

    for (int32_t i = 0; i < weights.size(); i++) { // Current layer
        for (int32_t j = 0; j < weights[i].size(); j++) { // Current layer, current neuron
            for (int32_t k = 0; k < weights[i][j].size(); k++) { // Next layer, current neuron
                neurons[i][k] += weights[i][j][k] * neurons[i][j];
            }
        }
    }

    return NeuralNetwork (topology, weights);
}

// Note: to get output length, just get NeuralNetwork's topology[layerCount - 1]!
std::vector<float> NeuralNetwork::FeedForward(std::vector<float> input) {
    // Pass inputs through NN.
    for (int32_t i = 0; i < weights.size(); i++) { // Current layer
        for (int32_t j = 0; j < weights[i].size(); j++) { // Current layer, current neuron
            for (int32_t k = 0; k < weights[i][j].size(); k++) { // Next layer, current neuron
                neurons[i][k] += weights[i][j][k] * neurons[i][j];
            }
        }
    }

    // Copy last layer's vals. to output.
    for (int32_t i = 0; i < topology[topology.size() - 1]; i++) {
        output[i] = neurons[topology.size()][i];
    }

    return output;
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

static float ActivationFunction(float input) {

}