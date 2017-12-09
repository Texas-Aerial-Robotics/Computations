#pragma once
class Agent
{

#pragma region Members
public:
	/// <summary>
	/// This agent's genotype.
	/// </summary>
	Genotype genotype;

	/// <summary>
	/// The feedforward neural network which was constructed from the genotype of this agent.
	/// </summary>
	NeuralNetwork fnn;

	/// <summary>
	/// Whether this Agent is currently active in a simulation.
	/// </summary>
	bool isAlive;
#pragma endregion
#pragma region Constructors
public:
	/// <summary>
	/// Initializes a new Agent from a given genotype, constructing a new feedforward neural network from the parameters of the genotype.
	/// </summary>
	/// <param name="genotype">The Genotype to initialize this Agent from.</param>
	/// <param name="defaultActivation">The default activation function to be used in the NeuralLayers of the feedforward neural network.</param>
	/// <param name="topology">The topology of the feedforward neural network to be constructed from the given Genotype.</param>
	Agent (Genotype genotype, std::vector<int> topology);
	~Agent();
#pragma endregion

#pragma region Methods
public:
	/// <summary>
	/// Called when this agent dies.
	/// </summary>
	void AgentDied ();

private:
	/// <summary>
	/// The neuron activation function to be used by all agents' NNs.
	/// </summary>
	static float NeuronActivationFunction(float input);
#pragma endregion
};
