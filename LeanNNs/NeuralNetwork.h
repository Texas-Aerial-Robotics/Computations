//
// Created by peter on 1/24/18.
//

#ifndef LEANNNS_NEURALNETWORK_H
#define LEANNNS_NEURALNETWORK_H

#include <stdint.h>
#include <vector>
class NeuralNetwork {
/* Things this class needs:
 * Neurons
 * Weights
 * Propogation function
 * Mutation function
 * Copy function
 * Random creation function
 * File IO (saving and loading NNs)
*/

// TODO: Random creation function, file IO.

    // 1-dimension:
    // 1. Current layer
    std::vector<int32_t> topology;

    // 2-dimensions:
    // 1. Current layer
    // 2. Current neuron
    std::vector<std::vector<float>> neurons;

    // 3-dimensions:
    // 1. Current layer
    // 2. Current neuron
    // 3. Current weight
    std::vector<std::vector<std::vector<float>>> weights;

    // Current output.
    std::vector<float> output; // TODO: Init. output: float output[topology[layerCount - 1]];

    const float weightMutChance = .5; // Chance of a given weight being mutated.
    const float minWeightMutProp = .5; // Min possible new weight value, prop. of weight's curr. val.
    const float maxWeightMutProp = 2; // Max possible new weight value as proportion of weight's current value

    // Creates a NN w/ the given topology and random weights.
    NeuralNetwork (std::vector<int32_t> topology);

    // Creates a NN w/ the given topology and weights.
    NeuralNetwork (std::vector<int32_t> topology, std::vector<std::vector<std::vector<float>>>);

    // Input: Old NN to copy.
    // Output: New NN w/ copied fields.
    NeuralNetwork DeepCopy (NeuralNetwork nnToCopy);

    // Input: float vector w/ its length
    // Returns a pointer to a float array representing this NN's output.
    std::vector<float> FeedForward(std::vector<float> input);

    // Mutates this NN.
    void Mutate();

    // Mutates the given weight if it should be mutated, returns new weight.
    static float MutateWeight(float input);

    // Implements a SoftSign activation function.
    static float ActivationFunction(float input);
};

#endif //LEANNNS_NEURALNETWORK_H
