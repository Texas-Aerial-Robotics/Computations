#include "stdafx.h"
#include "NeuralNetwork.h"

#pragma region Constructors
/// <summary>
/// Initializes a new fully connected feedforward neural network with a given topology.
/// </summary>
/// <param name="_topology">An array of integers representing the node count of each layer from the input layer to the output layer.</param>
NeuralNetwork::NeuralNetwork(std::vector<int> _topology) {
	topology = _topology;

	// Get the weight count of the given topology.
	weightCount = 0;
	// Initialize all the layers in the given topology.
	// (Ignore the output layer since it doesn't have 
	// any weights/neurons associated w/ its outputs.)
	std::vector<NeuralLayer> layers; layers.reserve(((int)topology.size()) - 1);
	for (int i = 0; i < ((int)topology.size()) - 1; i++) {
		// For each neuron in this layer, there is a connection to each neuron in the next layer, excluding the next layer's bias node.
		layers[i] = NeuralLayer(topology[i], topology[i + 1]);
		weightCount += ((topology[i] + 1) * topology[i + 1]); // +1 for the bias node in each layer.
	}
}

NeuralNetwork::~NeuralNetwork()
{
}
#pragma endregion

#pragma region Methods
/// <summary>
/// Process the given inputs using the current network's weights.
/// </summary>
/// <returns>The calculated outputs.</returns>
/// <param name="inputs">The inputs to be processed.</param>
std::vector<float> NeuralNetwork::ProcessInputs(std::vector<float> inputs) {
	// Check arguments.
	if (((int)inputs.size()) != layers[0].neuronCount) {
		throw new std::invalid_argument("The given inputs do not match the network input count.");
	}

	// Process inputs by propagating the input values through all this network's layers.
	std::vector<float> outputs = inputs;
	// Loop through all the layers in this neural network.
	// Pass the input values through the network to process them.
	for (int i = 0; i < ((int)layers.size()); i++) {
		outputs = layers[i].ProcessInputs(outputs);
	}
	return outputs;
}

/// <summary>
/// Sets the weights of this network to random values in a given range.
/// </summary>
/// <param name="minValue">The minimum value a weight may be set to.</param>
/// <param name="maxValue">The maximum value a weight may be set to.</param>
void NeuralNetwork::SetRandomWeights(float minValue, float maxValue) {
	// If this NeuralNetwork has been initialized, set random weights for its layers.
	if (((int)layers.size()) > 0) {
		// Loop through each layer in this NeuralNetwork, and set random values for each layer's weights.
		for (int i = 0; i < ((int)layers.size()); i++) {
			layers[i].SetRandomWeights(minValue, maxValue);
		}
	}
	else {
		throw "This NN has no layers!";
	}
}

/// <summary>
/// Returns a new NeuralNetwork instance with the same topology and
/// activation functions as this NeuralNetwork,
/// but with weights set to their default values.
/// </summary>
NeuralNetwork NeuralNetwork::GetTopologyCopy() {
	NeuralNetwork copy = NeuralNetwork(topology);

	return copy;
}

/// <summary>
/// Copies this NeuralNetwork including its topology and weights.
/// </summary>
/// <returns>A deep copy of this NeuralNetwork.</returns>
NeuralNetwork NeuralNetwork::DeepCopy() {
	NeuralNetwork newNet = NeuralNetwork(topology);
	// Copy all of this NeuralNetwork's layers into the new NeuralNetwork.
	for (int i = 0; i < ((int)layers.size()); i++) {
		newNet.layers[i] = layers[i].DeepCopy();
	}

	return newNet;
}

/* TODO: make a ToString-equivalent function.
/// <summary>
/// Returns a string representing this network in layer order.
/// </summary>
public override string ToString() {
	string output = "";

	for (int i = 0; i < layers.Length; i++) {
		output += "Layer " + i + ":\n" + layers[i].ToString();
	}

	return output;
}
*/
#pragma endregion
