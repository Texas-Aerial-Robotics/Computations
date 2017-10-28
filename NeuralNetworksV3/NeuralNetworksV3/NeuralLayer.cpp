#include "stdafx.h"
#include "NeuralLayer.h"

#pragma region Fields
float(NeuralLayer::*NeuronActivationFunction)(float input) = NULL;
#pragma endregion

#pragma region Constructors
/// <summary>
/// Initializes a new neural layer for a fully connected feedforward neural network with
/// a given number of nodes and with connections to the given number of nodes in the next layer.
/// </summary>
/// <param name="neuronCount">The number of (visible) nodes in this layer.</param>
/// <param name="outputCount">The number of (visible) nodes in the next layer.</param>
NeuralLayer::NeuralLayer(int _neuronCount, int _outputCount)
{
	// Note to self: The "this" keyword is a pointer to the object (a NeuralLayer in this 
	// case) being created. Arrows are used w/ pointers to objects. Dots are used w/ actual objects.
	neuronCount = _neuronCount;
	outputCount = _outputCount;

	// Fully initialize the weights array.
	weights.reserve(neuronCount + 1); // Allow for 1 bias neuron per NeuralLayer (hence neuronCount + 1).
	for (int i = 0; i < (int)weights.size(); i++) {
		weights[i] = std::vector<float>();
		weights[i].reserve(_outputCount);
	}
}

// TODO: Implement destructor?
NeuralLayer::~NeuralLayer()
{
}
#pragma endregion

#pragma region Methods
/// <summary>
/// Sets the weights of this layer to given values.
/// Example: In a layer of 2 neurons w/ the next layer having 3 neurons,
/// the values [0-2] are the weights from neuron 0 of this layer to neurons 0-2 of the next.
/// The vals. [3-5] are the weights from neuron 1 of this layer to neurons 0-2 of the next.
/// </summary>
void NeuralLayer::SetWeights(std::vector<float> _weights) {
	// Check arguments.
	if (_weights.size() != weights.size()) {
		throw new std::invalid_argument("Input weights do not match this layer's weight count.");
	}

	// Copy weights from the given weights array.
	int k = 0;
	// (i has to be a "size_t" not an int, since C++ can't compare size_t's (vector sizes) w/ ints.)
	for (size_t i = 0; i < weights.size(); i++) {
		for (size_t j = 0; j < weights[i].size(); j++) {
			weights[i][j] = _weights[k++];
		}
	}
}

/// <summary>
/// Uses the current weights to process given inputs for use in the next layer.
/// </summary>
/// <returns>The calculated outputs.</returns>
std::vector<float> NeuralLayer::ProcessInputs(std::vector<float> inputs) {
	// Check arguments.
	if (inputs.size() != neuronCount) {
		throw new std::invalid_argument("The given inputs do not match this layer's input count.");
	}

	// Calculate the output sum for each neuron from weighted inputs and bias.
	std::vector<float> outputs; outputs.reserve(outputCount);
	// Add a bias (always-on neuron to inputs)
	std::vector<float> biasedInputs = inputs; biasedInputs.reserve(neuronCount + 1); // (neuronCount + 1 for the bias neuron.)
	biasedInputs[biasedInputs.size()] = 1.0f; // The bias neuron is always on (outputs a val. of 1).

	// Loop through ea. of this layer's neurons,
	// properly adding weighted output vals. to the outputs vector.
	for (size_t i = 0; i < weights.size(); i++) {
		for (size_t j = 0; j < weights[i].size(); j++) {
			outputs[j] += biasedInputs[i] * weights[i][j];
		}
	}

	// If an activation function is set,
	// apply an activation function to the output values.
	if ((*NeuralLayer::NeuronActivationFunction) != NULL) {
		// Loop through ea. of the output values, give them processed vals.
		for (size_t i = 0; i < outputs.size(); i++) {
			outputs[i] = (*NeuralLayer::NeuronActivationFunction)(outputs[i]);
		}
	}
	else {
		throw "No activation function!";
	}

	return outputs;
}

/// <summary>
/// Copies this NeuralLayer including its weights.
/// </summary>
/// <returns>A deep copy of this NeuralLayer.</returns>
NeuralLayer NeuralLayer::DeepCopy() {
	// Copy weights.
	std::vector<std::vector<float>> copiedWeights; copiedWeights.reserve(weights.size());

	for (size_t i = 0; i < weights.size(); i++) {
		for (size_t j = 0; j < weights[i].size(); j++) {
			copiedWeights[i][j] = weights[i][j];
		}
	}

	// Create the copied NeuralLayer.
	NeuralLayer newLayer = NeuralLayer(neuronCount, outputCount);
	newLayer.weights = copiedWeights;

	return newLayer;
}

/// <summary>
/// Sets the weights of the connections from this layer to the next to random values in a given range.
/// </summary>
/// <param name="minValue">The minimum value that a weight may be set to.</param>
/// <param name="maxValue">The minimum value that a weight may be set to.</param>
void NeuralLayer::SetRandomWeights(float minValue, float maxValue) {
	// Loop through all the weights of this neural layer,
	// and give them random vals. b/w minValue and maxValue.
	float normalizedRand; // A normalized, random float (b/w 0 and 1).
	float range = maxValue - minValue; // The range b/w minValue and maxValue.
	for (size_t i = 0; i < weights.size(); i++) {
		for (size_t j = 0; j < weights[i].size(); j++) {
			normalizedRand = ((float)rand()) / (float(RAND_MAX));
			weights[i][j] = minValue + normalizedRand * range;
		}
	}
}

// TODO: Add a ToString function!