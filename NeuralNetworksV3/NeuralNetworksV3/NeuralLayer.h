#pragma once
#include <vector>
class NeuralLayer
{
public:
#pragma region Function Pointers
	static float NeuronActivationFunction(float input);
#pragma endregion

#pragma region Fields
	/// <summary>
	/// The number of neurons in this layer.
	/// </summary>
	int neuronCount;

	/// <summary>
	/// The number of neurons in the next layer that this layer is connected to
	/// (i.e. the number of neurons in the next layer minus the number of "bias neurons" in that layer). 
	/// </summary>
	int outputCount;

	/// <summary>
	/// The weights of the connections of this layer to the next layer.
	/// Example: weight[i][j] is the weight of the connection from the 
	/// i-th neuron of this layer to the j-th neuron of the next layer.
	/// </summary>
	std::vector<std::vector<float>> weights;
#pragma endregion

#pragma region Constructors
public:
	~NeuralLayer();
	NeuralLayer(int _neuronCount, int _outputCount);
#pragma endregion

#pragma region Methods
	void SetWeights(std::vector<float> _weights);

	std::vector<float> ProcessInputs(std::vector<float> inputs);

	NeuralLayer DeepCopy();

	void SetRandomWeights(float minValue, float maxValue);

	// TODO: Add a ToString function!
#pragma endregion
};

