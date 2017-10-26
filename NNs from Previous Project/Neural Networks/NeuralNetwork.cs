using System;
using UnityEngine;

public class NeuralNetwork {
	#region Members
	/// <summary>
	/// An array representing the individual neural layers of this network.
	/// </summary>
	public NeuralLayer[] layers { get; private set;}

	/// <summary>
	/// An array of integers representing the node count of each 
	/// layer of the network from the input to output layers.
	/// </summary>
	public int[] topology { get; private set;}

	/// <summary>
	/// The total number of weights for the connections of this network.
	/// </summary>
	public int weightCount { get; private set;}
	#endregion

	#region Constructors
	/// <summary>
	/// Initializes a new fully connected feedforward neural network with a given topology.
	/// </summary>
	/// <param name="topology">An array of integers representing the node count of each layer from the input layer to the output layer.</param>
	public NeuralNetwork (int[] topology) {
		this.topology = topology;

		// Get the weight count of the given topology.
		weightCount = 0;
		// Loop through all the layers in the given topology.
		// (Ignore the input layer.)
		for (int i = 0; i < topology.Length - 1; i++) {
			// For each neuron in this layer, there is a connection to each neuron in the next layer, excluding the next layer's bias node.
			weightCount += ((topology [i] + 1) * topology [i + 1]); // +1 for the bias node in each layer.
		}

		// Initialize layers.
		// (Exclude the first layer in the network, since that's just the input layer.)
		// (The input layer's values aren't weighted before they're passed to the next layer.)
		layers = new NeuralLayer[topology.Length - 1];
		for (int i = 0; i < layers.Length; i++) {
			layers[i] = new NeuralLayer(topology[i], topology[i + 1]);
		}
	}
	#endregion

	#region Methods
	/// <summary>
	/// Process the given inputs using the current network's weights.
	/// </summary>
	/// <returns>The calculated outputs.</returns>
	/// <param name="inputs">The inputs to be processed.</param>
	public float[] ProcessInputs (float[] inputs) {
		// Check arguments.
		if (inputs.Length != layers [0].neuronCount) {
			throw new ArgumentException ("The given inputs do not match the network input count.");
		}

		// Process inputs by propagating the input values through all this network's layers.
		float[] outputs = inputs;
		// Loop through all the layers in this neural network.
		// Pass the input values through the network to process them.
		for (int i = 0; i < layers.Length; i++) {
			outputs = layers [i].ProcessInputs (outputs);
		}
		return outputs;
	}

	/// <summary>
	/// Sets the weights of this network to random values in a given range.
	/// </summary>
	/// <param name="minValue">The minimum value a weight may be set to.</param>
	/// <param name="maxValue">The maximum value a weight may be set to.</param>
	public void SetRandomWeights (float minValue, float maxValue) {
		Debug.Log ("Progress...");
		// If this NeuralNetwork has been initialized, set random weights for this neural network's layers.
		if (layers != null) {
			Debug.Log ("We have layers.");
			// Loop through each layer in this NeuralNetwork, and set random values for each layer's weights.
			for (int i = 0; i < layers.Length; i++) {
				layers [i].SetRandomWeights (minValue, maxValue);
			}
		}
	}

	/// <summary>
	/// Returns a new NeuralNetwork instance with the same topology and
	/// activation functions as this NeuralNetwork,
	/// but with weights set to their default values.
	/// </summary>
	public NeuralNetwork GetTopologyCopy () {
		NeuralNetwork copy = new NeuralNetwork (this.topology);
		for (int i = 0; i < layers.Length; i++) {
			copy.layers [i].NeuronActivationFunction = this.layers [i].NeuronActivationFunction;
		}

		return copy;
	}

	/// <summary>
	/// Copies this NeuralNetwork including its topology and weights.
	/// </summary>
	/// <returns>A deep copy of this NeuralNetwork.</returns>
	public NeuralNetwork DeepCopy () {
		NeuralNetwork newNet = new NeuralNetwork (this.topology);
		// Copy all of this NeuralNetwork's layers into the new NeuralNetwork.
		for (int i = 0; i < this.layers.Length; i++) {
			newNet.layers [i] = this.layers [i].DeepCopy ();
		}

		return newNet;
	}

	/// <summary>
	/// Returns a string representing this network in layer order.
	/// </summary>
	public override string ToString () {
		string output = "";

		for (int i = 0; i < layers.Length; i++) {
			output += "Layer " + i + ":\n" + layers [i].ToString ();
		}

		return output;
	}
	#endregion
}
