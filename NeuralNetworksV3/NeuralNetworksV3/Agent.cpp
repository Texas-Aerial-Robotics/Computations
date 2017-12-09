#include "stdafx.h"
#include "Agent.h"
#include "GeneticsManager.cpp"

/// <summary>
/// Initializes a new Agent from a given genotype, constructing a new feedforward neural network from the parameters of the genotype.
/// </summary>
/// <param name="genotype">The Genotype to initialize this Agent from.</param>
/// <param name="defaultActivation">The default activation function to be used in the NeuralLayers of the feedforward neural network.</param>
/// <param name="topology">The topology of the feedforward neural network to be constructed from the given Genotype.</param>
Agent::Agent (Genotype genotype, std::vector<int> topology) {
	isAlive = false;
	this->genotype = genotype;
	fnn = NeuralNetwork(topology);

	// Check if the given topology is valid with the given genotype.
	if (fnn.weightCount != genotype.GetParameterCount())
		throw new std::invalid_argument ("The given genotype's parameter count must match the neural network topology's weight count.");

	// Construct a feedforward neural network (FNN) from the given genotype.
	std::vector<float> parameters = genotype.GetParameterCopy ();
	unsigned int parameterIndex = 0; // Current index w/in parameters.
	for (int i = 0; i < fnn.layers.size; i++) {// Loop over all the layers in the NeuralNetwork.
		NeuralLayer layer = fnn.layers[i];

		for (unsigned int i = 0; i < layer.weights.size(); i++) { // Loop over all the nodes of the current layer.
			for (unsigned int j = 0; j < layer.weights[i].size(); j++) { // Loop over all the nodes of the next layer.
				layer.weights[i][j] = parameters [parameterIndex++];
			}
		}
	}
}

void Agent::AgentDied() {
	GeneticsManager::instance.OnAgentDied (*this);
}

float Agent::NeuronActivationFunction(float input) {
	return MathHelper::SoftSignFunction(input);
}
