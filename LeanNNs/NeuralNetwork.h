//
// Created by peter on 1/24/18.
//

#ifndef LEANNNS_NEURALNETWORK_H
#define LEANNNS_NEURALNETWORK_H

#include <stdint.h>
#include <vector>
class NeuralNetwork {
/* Things this class has:
 * Neurons
 * Weights
 * Propogation function
 * Mutation function
 * Copy function
 * Random creation function
 * File IO (saving and loading NNs)
*/

    // Weight stuff.
    const float minInitWeight = -1;
    const float maxInitWeight = 1;
    static constexpr float weightMutChance = .75;
    static constexpr float minWeightMutCoeff = .25;
    static constexpr float maxWeightMutCoeff = 4;
    static constexpr float minWeightMutOffset = -1;
    static constexpr float maxWeightMutOffset = 1;

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

public:
    // Creates a NN w/ the given topology and random weights.
    NeuralNetwork (std::vector<int32_t> topology);

    // Creates a NN w/ the given topology and weights.
    // Assumes given weights is independent of other NNs.
    NeuralNetwork (std::vector<int32_t> topology, std::vector<std::vector<std::vector<float>>> weights);

    // Input: Old NN to copy.
    // Output: New NN w/ copied fields.
    NeuralNetwork DeepCopy (NeuralNetwork nnToCopy);

    // Reads NN from file at path.
    static NeuralNetwork* ReadFromFile (char path[]);

    // Writes the given NN to the file at path.
    static void WriteToFile (NeuralNetwork nn, char path[]);

    // Input: float vector w/ its length
    // Returns a pointer to a float array representing this NN's output.
    std::vector<float> FeedForward(std::vector<float> input);

    // Mutates this NN.
    void Mutate();

// Helper functions:
private:
    // Allocates weights given a topology.
    static std::vector<std::vector<std::vector<float>>> AllocWeights (std::vector<int32_t> topology);

    // Mutates the given weight if it should be mutated, returns new weight.
    static float MutateWeight(float weight);

    // Implements a SoftSign activation function.
    static float ActivationFunction(float input);

    // Returns a random float b/w minVal and maxVal.
    static float RandRange (float minVal, float maxVal);

    // Floating point absolute value function.
    static float Abs (float input);

    static void WriteCharsToFile (char* chars, uint32_t length, FILE* fileStream);

    static void ReadCharsFromFile (char* chars, uint32_t length, FILE* fileStream);

// Debugging stuff:
public:
    // Prints this NN's weights.
    void PrintWeights();
};

#endif //LEANNNS_NEURALNETWORK_H
