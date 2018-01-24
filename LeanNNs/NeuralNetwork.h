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
*/

    // 1-dimensional.
    int32_t topology[];
    int32_t layerCount;

    // 2-dimensional
    float neurons[];

    // 3-dimensional
    float weights[];

    // Input: float array w/ its length
    // Returns a pointer to a float array representing this NN's output.
    int* FeedForward (float input[], int inputLength);
};


#endif //LEANNNS_NEURALNETWORK_H
