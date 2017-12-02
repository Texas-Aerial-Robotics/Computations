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
	fnn = new NeuralNetwork(topology);
	foreach(NeuralLayer layer in fnn.layers) {
		layer.NeuronActivationFunction = defaultActivation;
	}

	// Check if the given topology is valid with the given genotype.
	if (fnn.weightCount != genotype.parameterCount)
		throw new std::invalid_argument ("The given genotype's parameter count must match the neural network topology's weight count.");

	// Construct a feedforward neural network (FNN) from the given genotype.
	IEnumerator<float> parameters = genotype.GetEnumerator();
	foreach(NeuralLayer layer in fnn.layers) { // Loop over all the layers in the NeuralNetwork.
		for (int i = 0; i < layer.weights.Length; i++) { // Loop over all the nodes of the current layer.
			for (int j = 0; j < layer.weights[i].Length; j++) { // Loop over all the nodes of the next layer.
				layer.weights[i][j] = parameters.Current;
				parameters.MoveNext();
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
