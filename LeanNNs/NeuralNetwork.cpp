//
// Created by peter on 1/24/18.
//

#include "NeuralNetwork.h"

int* NeuralNetwork::FeedForward(float *input, int32_t inputLength) { // Cool! float* is the same as float[]!
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
}