//
// Created by peter on 1/24/18.
//

#include "NeuralNetwork.h"

// TODO: Implement activation and weight mutation functions.

NeuralNetwork NeuralNetwork::DeepCopy(NeuralNetwork nnToCopy) {
    int layerCount = nnToCopy.layerCount;
    int topology[layerCount];

    for (int32_t i = 0; i < layerCount; i++) {
        topology[i] = nnToCopy.topology[i];
    }

    // Just deep copy weights: neurons and output are essentially temp variables:
    int32_t weightCount = nnToCopy.weightCount;
    float weights[weightCount];

    int32_t prevLayerNeurons = 0; // Total neuron count of all previous layers.
    int32_t currentLayerNeurons = 0; // Neuron count of current layer.
    for (int32_t i = 0; i < layerCount - 1; i++) { // Current layer
        currentLayerNeurons = topology[i];

        for (int32_t j = 0; j < currentLayerNeurons; j++) { // Current neuron, current layer.
            for (int32_t k = 0; k < topology[i + 1]; k++) { // Current neuron, next layer.
                weights[prevLayerNeurons + currentLayerNeurons + k] =
                        nnToCopy.weights[prevLayerNeurons + currentLayerNeurons + k];
            }

        }

        prevLayerNeurons += currentLayerNeurons;
    }
}

// Note: to get output length, just get NeuralNetwork's topology[layerCount - 1]!
int32_t* NeuralNetwork::FeedForward(float* input, int32_t inputLength) { // Cool! float* is the same as float[]!
    int32_t prevLayerNeurons = 0; // Total neuron count of all previous layers.
    int32_t currentLayerNeurons = 0; // Neuron count of current layer.
    for (int32_t i = 0; i < layerCount - 1; i++) { // Current layer
        currentLayerNeurons = topology[i];

        for (int32_t j = 0; j < currentLayerNeurons; j++) { // Current neuron, current layer.
            for (int32_t k = 0; k < topology[i + 1]; k++) { // Current neuron, next layer.
                neurons[prevLayerNeurons + currentLayerNeurons + k] += ActivationFunction(neurons[prevLayerNeurons + j]);
            }

        }

        prevLayerNeurons += currentLayerNeurons;
    }

    prevLayerNeurons -= currentLayerNeurons; // Get back to the START of the last layer.
    for (int32_t i = prevLayerNeurons, j = 0; j < topology[layerCount - 1]; i++, j++) {
        output[j] = neurons[i];
    }
    return (int32_t*) output;
}

void NeuralNetwork::Mutate() {
    int32_t prevLayerNeurons = 0; // Total neuron count of all previous layers.
    int32_t currentLayerNeurons = 0; // Neuron count of current layer.
    for (int32_t i = 0; i < layerCount - 1; i++) { // Current layer
        currentLayerNeurons = topology[i];

        for (int32_t j = 0; j < currentLayerNeurons; j++) { // Current neuron, current layer.

            for (int32_t k = 0; k < topology[i + 1]; k++) { // Current neuron, next layer.
                // Mutate current weight!
                weights[prevLayerNeurons + currentLayerNeurons + k] = MutateWeight (weights[prevLayerNeurons + currentLayerNeurons + k]);
            }

        }

        prevLayerNeurons += currentLayerNeurons;
    }
}