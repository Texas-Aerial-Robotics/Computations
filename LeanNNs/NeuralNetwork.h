//
// Created by peter on 1/24/18.
//

#ifndef LEANNNS_NEURALNETWORK_H
#define LEANNNS_NEURALNETWORK_H

#include <stdint.h>
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

    // 1-dimensional.
    int32_t topology[];
    int32_t layerCount; // How many layers this NN has.

    // 2-dimensional
    float neurons[];

    // 3-dimensional
    float weights[];
    int32_t weightCount;

    // Current output.
    float output[]; // TODO: Init. output: float output[topology[layerCount - 1]];
    int32_t outputCount; // TODO: init. output count and other counts!

    const float weightMutChance = .5; // Chance of a given weight being mutated.
    const float minWeightMutProp = .5; // Min possible new weight value, prop. of weight's curr. val.
    const float maxWeightMutProp = 2; // Max possible new weight value as proportion of weight's current value

    // Input: Old NN to copy.
    // Output: New NN w/ copied fields.
    NeuralNetwork DeepCopy (NeuralNetwork nnToCopy);

    // Input: float array w/ its length
    // Returns a pointer to a float array representing this NN's output.
    int32_t* FeedForward(float input[], int inputLength);

    // Mutates this NN.
    void Mutate();

    // Mutates the given weight if it should be mutated, returns new weight.
    static float MutateWeight(float input);

    // Implements a SoftSign activation function.
    static float ActivationFunction(float input);
};

#endif //LEANNNS_NEURALNETWORK_H
