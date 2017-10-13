#include "stdafx.h"
#include <vector>

using namespace std;

class NeuralLayer {

	/* 
	// Notes to myself:
	// "Pointer": a variable that stores the *address* of another variable
	// & - the "address-of operator"; read as "address of"

	// * - the "dereference operator"; read as "value pointed to by"

	// So the & (address-of operator) and * (dereference operator) are complementary.

	// Pointers are declared with the following syntax...
	// type * name (of the pointer)
	// (The asterisk here is NOT the dereference operator)

	// Function pointers:
	// Declared like a regular function, except the name of a function pointer is enclosed b/w parantheses, and an asterisk is inserted before the name.
	// Ex: Declaring a function pointer called "FuncPointer" that represents a function that takes a string and an int and returns a float:
	// float (*FuncPointer) (string, int)
	// ^-- (This is like "dereferencing" FuncPointer, which is the address of some function.)
	// The actual function that FuncPointer represents might be declared as "float Function (string, int)".
	//
	// Syntax for setting a function pointer's value:
	// (function_pointer_name) = &(function_name)
	// The ampersand is optional, so we can also do this to point the function pointer to the function...
	// (function_pointer_name) = (function_name)
	//
	// You also don't need to use an asterisk when calling the function associated w/ a function pointer.
	// (C++ will automatically dereference a function pointer when it's called as a function.)
	// Ex: *function_pointer_name (arguments)" is the same as "function_pointer_name (arguments)" in C++.
	*/

#pragma region Function Pointers
public:
	/// <summary>
	/// Delegate representing the activation function of an artificial neuron.
	/// </summary>
	/// <param name="input">The input value of the function.</param>
	/// <returns>The calculated output value of the function.</returns>
	float(*NeuronActivationFunction)(float input) = NULL;
#pragma endregion

#pragma region Fields
private:
	/// <summary>
	/// The number of neurons in this layer.
	/// </summary>
	int neuronCount;

	/// <summary>
	/// The number of neurons in the next layer that this layer is connected to
	/// (i.e. the number of neurons in the next layer minus the number of "bias neurons" in that layer). 
	/// </summary>
	int outputCount;

public:
	/// <summary>
	/// The weights of the connections of this layer to the next layer.
	/// Example: weight[i][j] is the weight of the connection from the 
	/// i-th neuron of this layer to the j-th neuron of the next layer.
	/// </summary>
	vector<vector<float>> weights;
#pragma endregion

#pragma region Constructors
public:
	/// <summary>
	/// Initializes a new neural layer for a fully connected feedforward neural network with
	/// a given number of nodes and with connections to the given number of nodes in the next layer.
	/// </summary>
	/// <param name="neuronCount">The number of (visible) nodes in this layer.</param>
	/// <param name="outputCount">The number of (visible) nodes in the next layer.</param>
	NeuralLayer(int neuronCount, int outputCount) {
		// Note to self: The "this" keyword is a pointer to the object (a NeuralLayer in this 
		// case) being created. Arrows are used w/ pointers to objects. Dots are used w/ actual objects.
		this->neuronCount = neuronCount;
		this->outputCount = outputCount;

		// Fully initialize the weights array.
		weights.reserve(neuronCount + 1); // Allow for 1 bias neuron per NeuralLayer (hence neuronCount + 1).
		for (int i = 0; i < (int)weights.size(); i++) {
			weights[i] = vector<float>();
			weights[i].reserve(outputCount);
		}
	}
#pragma endregion

#pragma region Methods
public:
	/// <summary>
	/// Sets the weights of this layer to given values.
	/// Example: In a layer of 2 neurons w/ the next layer having 3 neurons,
	/// the values [0-2] are the weights from neuron 0 of this layer to neurons 0-2 of the next.
	/// The vals. [3-5] are the weights from neuron 1 of this layer to neurons 0-2 of the next.
	/// </summary>
	void SetWeights(vector<float> weights) {
		// Check arguments.
		if (weights.size() != this->weights.size()) {
			throw new invalid_argument("Input weights do not match this layer's weight count.");
		}

		// Copy weights from the given weights array.
		int k = 0;
		// (i has to be a "size_t" not an int, since C++ can't compare size_t's (vector sizes) w/ ints.)
		for (size_t i = 0; i < this->weights.size(); i++) {
			for (size_t j = 0; j < this->weights[i].size(); j++) {
				this->weights[i][j] = weights[k++];
			}
		}
	}

	/// <summary>
	/// Uses the current weights to process given inputs for use in the next layer.
	/// </summary>
	/// <returns>The calculated outputs.</returns>
	vector<float> ProcessInputs(vector<float> inputs) {
		// Check arguments.
		if (inputs.size() != neuronCount) {
			throw new invalid_argument("The given inputs do not match this layer's input count.");
		}

		// Calculate the output sum for each neuron from weighted inputs and bias.
		vector<float> outputs = vector<float>(); outputs.reserve(outputCount);
		// Add a bias (always-on neuron to inputs)
		vector<float> biasedInputs = inputs; biasedInputs.reserve(neuronCount + 1); // (neuronCount + 1 for the bias neuron.)
		biasedInputs[biasedInputs.size()] = 1.0f; // The bias neuron is always on (outputs a val. of 1).

		// Loop through ea. of this layer's neurons,
		// properly adding weighted output vals. to the outputs vector.
		for (size_t i = 0; i < this->weights.size(); i++) {
			for (size_t j = 0; j < this->weights[i].size(); j++) {
				outputs[j] += biasedInputs[i] * weights[i][j];
			}
		}

		// If an activation function is set,
		// apply an activation function to the output values.
		if (NeuronActivationFunction != NULL) {
			// Loop through ea. of the output values, give them processed vals.
			for (size_t i = 0; i < outputs.size(); i++) {
				outputs[i] = NeuronActivationFunction(outputs[i]);
			}
		}
		
		return outputs;
	}

	/// <summary>
	/// Copies this NeuralLayer including its weights.
	/// </summary>
	/// <returns>A deep copy of this NeuralLayer.</returns>
	NeuralLayer DeepCopy() {
		// Copy weights.
		vector<vector<float>> copiedWeights; copiedWeights.reserve(weights.size());

		for (size_t i = 0; i < weights.size(); i++) {
			for (size_t j = 0; j < weights[i].size(); j++) {
				copiedWeights[i][j] = weights[i][j];
			}
		}

		// Create the copied NeuralLayer.
		NeuralLayer newLayer = NeuralLayer(this->neuronCount, this->outputCount);
		newLayer.weights = copiedWeights;
		newLayer.NeuronActivationFunction = this->NeuronActivationFunction;

		return newLayer;
	}

	/// <summary>
	/// Sets the weights of the connections from this layer to the next to random values in a given range.
	/// </summary>
	/// <param name="minValue">The minimum value that a weight may be set to.</param>
	/// <param name="maxValue">The minimum value that a weight may be set to.</param>
	void SetRandomWeights(float minValue, float maxValue) {
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
#pragma endregion
};