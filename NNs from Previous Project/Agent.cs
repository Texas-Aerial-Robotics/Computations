using System;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Class that combines a genotype and a feedforward neural network (FNN).
/// </summary>
public class Agent : IComparable<Agent> {
	#region Members
	/// <summary>
	/// The underlying genotype of this agent.
	/// </summary>
	public Genotype genotype { get; private set; }

	/// <summary>
	/// The feedforward neural network which was constructed from the genotype of this agent.
	/// </summary>
	/// <value>The f N.</value>
	public NeuralNetwork fnn { get; private set; }

	private bool _isAlive = false;
	/// <summary>
	/// Whether this agent is currently alive (actively participating in a simulation).
	/// </summary>
	public bool isAlive {
		get { return _isAlive; }

		private set {
			// Don't do anything if _isAlive isn't being changed.
			if (_isAlive != value) {
				_isAlive = value;

				// Call the AgentDied delegate if it's not null and this agent is dead.
				// (This is 'if' statement is only activated where an Agent is alive, and _isAlive is being set to false.)
				if (!_isAlive && AgentDied != null)
					AgentDied (this);
			}
		}
	}

	/// <summary>
	/// Event for when this agent has died (stopped participating in the simulation).
	/// </summary>
	public event Action<Agent> AgentDied;
	#endregion

	#region Constructors
	/// <summary>
	/// Initializes a new Agent from a given genotype, constructing a new feedforward neural network from the parameters of the genotype.
	/// </summary>
	/// <param name="genotype">The Genotype to initialize this Agent from.</param>
	/// <param name="defaultActivation">The default activation function to be used in the NeuralLayers of the feedforward neural network.</param>
	/// <param name="topology">The topology of the feedforward neural network to be constructed from the given Genotype.</param>
	public Agent (Genotype genotype, NeuralLayer.ActivationFunction defaultActivation, params int[] topology) {
		isAlive = false;
		this.genotype = genotype;
		fnn = new NeuralNetwork (topology);
		foreach (NeuralLayer layer in fnn.layers) {
			layer.NeuronActivationFunction = defaultActivation;
		}

		// Check if the given topology is valid with the given genotype.
		if (fnn.weightCount != genotype.parameterCount)
			throw new ArgumentException ("The given genotype's parameter count must match the neural network topology's weight count.");

		// Construct a feedforward neural network (FNN) from the given genotype.
		IEnumerator<float> parameters = genotype.GetEnumerator ();
		foreach (NeuralLayer layer in fnn.layers) { // Loop over all the layers in the NeuralNetwork.
			for (int i = 0; i < layer.weights.Length; i++) { // Loop over all the nodes of the current layer.
				for (int j = 0; j < layer.weights[i].Length; j++) { // Loop over all the nodes of the next layer.
					layer.weights[i][j] = parameters.Current;
					parameters.MoveNext ();
				}
			}
		}
	}
	#endregion

	#region Methods
	/// <summary>
	/// Resets this agent to be alive again.
	/// </summary>
	public void Reset () {
		genotype.evaluation = 0;
		genotype.fitness = 0;
		isAlive = true;
	}

	/// <summary>
	/// Kills this agent (sets isAlive (NOT merely _isAlive) to false).
	/// </summary>
	public void Kill () {
		isAlive = false;
	}

	#region IComparable
	/// <summary>
	/// Compares this agent to another agent by comparing their underlying genotypes.
	/// </summary>
	/// <returns>The result of comparing the underlying genotypes of this agent and the given agent.</returns>
	/// <param name="other">The agent to compare this agent to.</param>
	public int CompareTo (Agent other) {
		return this.genotype.CompareTo (other.genotype);
	}
	#endregion
	#endregion
}
