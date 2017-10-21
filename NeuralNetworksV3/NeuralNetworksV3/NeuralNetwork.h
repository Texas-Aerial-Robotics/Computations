#pragma once
#include <vector>
#include "NeuralLayer.h"
class NeuralNetwork
{
public:
#pragma region Fields
	/// <summary>
	/// An array representing the individual neural layers of this network.
	/// </summary>
	std::vector<NeuralLayer> layers;

	/// <summary>
	/// An array of integers representing the node count of each 
	/// layer of the network from the input to output layers.
	/// </summary>
	std::vector<int> topology;

	/// <summary>
	/// The total number of weights for the connections of this network.
	/// </summary>
	int weightCount;
#pragma endregion


#pragma region Constructors
	NeuralNetwork(std::vector<int> _topology);
	~NeuralNetwork();
#pragma endregion

#pragma region Methods
	std::vector<float> ProcessInputs(std::vector<float> _inputs);

	void SetRandomWeights(float minValue, float maxValue);

	NeuralNetwork GetTopologyCopy();

	NeuralNetwork DeepCopy();
#pragma endregion
};

