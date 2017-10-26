using System;

/// <summary>
/// Class representing a single layer of a fully connected feedforward neural network.
/// </summary>
public class NeuralLayer {
	/// <summary>
	/// Delegate representing the activation function of an artificial neuron.
	/// </summary>
	/// <param name="input">The input value of the function.</param>
	/// <returns>The calculated output value of the function.</returns>
	public delegate float ActivationFunction (float input);

	public ActivationFunction NeuronActivationFunction = MathHelper.SigmoidFunction;
	#region Members
	/// <summary>
	/// The number of neurons in this layer.
	/// </summary>
	public int neuronCount { get; private set;}

	/// <summary>
	/// The number of neurons in the next layer that this layer is connected to (i.e. the number of neurons in the next layer).
	/// </summary>
	public int outputCount {get; private set;}

	/// <summary>
	/// The weights of the connections of this layer to the next layer.
	/// Example: weight[i][j] is the weight of the connection from the i-th neuron of this layer to the j-th neuron of the next layer.
	/// </summary>
	public float[][] weights {
		get;
		private set;
	}
	#endregion

	#region Constructors
	/// <summary>
	/// Initializes a new neural layer for a fully connected feedforward neural network with
	/// a given number of nodes and with connections to the given number of nodes in the next layer.
	/// </summary>
	/// <param name="nodeCount">The number of nodes in this layer.</param>
	/// <param name="outputCount">The number of nodes in the next layer.</param>
	/// <remarks>All weights of the connections from this layer to the next are initialized with the default value.</remarks>
	public NeuralLayer (int neuronCount, int outputCount) {
		this.neuronCount = neuronCount;
		this.outputCount = outputCount;

		// Fully initialize the weights array.
		weights = new float[neuronCount + 1][]; // There are neuronCount + 1 slots in the first dimension of the weights array to allow for one bias neuron per NeuralLayer.

		for (int i = 0; i < weights.Length; i++) {
			weights[i] = new float[outputCount];
		}
	}
	#endregion

	#region Methods
	/// <summary>
	/// Sets the weights of this layer to given values.
	/// Example: In a layer with 2 neurons with the next layer having 3 neurons,
	/// the values [0-2] are the weights from neuron 0 of this layer to neurons 0-2 of the next layer, respectively, and
	/// the values [3-5] are the weights from neuron 1 of this layer to neurons 0-2 of the next layer, respectively.
	/// </summary>
	/// <param name="weights">Weights.</param>
	public void SetWeights (float[] weights) {
		// Check arguments.
		if (weights.Length != this.weights.Length) {
			throw new ArgumentException ("Input weights do not match this layer's weight count.");
		}

		// Copy weights from the given weights array.
		int k = 0;
		for (int i = 0; i < this.weights.Length; i++) {
			for (int j = 0; j < this.weights[i].Length; j++) {
				this.weights [i] [j] = weights [k++];
			}
		}
	}

	/// <summary>
	/// Processes the given inputs using the current weights for use in the next layer.
	/// </summary>
	/// <returns>The calculated outputs.</returns>
	/// <param name="inputs">The inputs to be processed.</param>
	public float[] ProcessInputs (float[] inputs) {
		// Check arguments.
		if (inputs.Length != neuronCount) {
			throw new ArgumentException ("The given inputs do not match this layer's input count.");
		}

		// Calculate the output sum for each neuron from weighted inputs and bias.
		float[] outputs = new float[outputCount];
		// Add a "bias" (always on) neuron to inputs.
		// The bias neuron is at the last index of the biasedInputs array.
		float[] biasedInputs = new float[neuronCount + 1];
		inputs.CopyTo (biasedInputs, 0);
		biasedInputs [inputs.Length] = 1f;

		// Loop through each of this layer's neurons,
		// properly adding weighted output values to the outputs array.
		for (int i = 0; i < this.weights.Length; i++) {
			for (int j = 0; j < this.weights[i].Length; j++) {
				outputs[j] += biasedInputs[i] * weights [i][j];
			}
		}

		// If an activation function is set,
		// apply an activation function to the output values.
		if (NeuronActivationFunction != null) {
			// Loop through each of the output values, and apply the activation function to those values.
			for (int i = 0; i < outputs.Length; i++) {
				outputs [i] = NeuronActivationFunction (outputs [i]);
			}
		}

		return outputs;
	}

	/// <summary>
	/// Copies this NeuralLayer including its weights.
	/// </summary>
	/// <returns>A deep copy of this NeuralLayer.</returns>
	public NeuralLayer DeepCopy () {
		// Copy weights.
		float[][] copiedWeights = new float[weights.Length][];

		for (int i = 0; i < weights.Length; i++) {
			for (int j = 0; j < weights[i].Length; j++) {
				copiedWeights [i] [j] = weights [i] [j];
			}
		}

		// Create the copied NeuralLayer.
		NeuralLayer newLayer = new NeuralLayer(this.neuronCount, this.outputCount);
		newLayer.weights = copiedWeights;
		newLayer.NeuronActivationFunction = this.NeuronActivationFunction;

		return newLayer;
	}

	/// <summary>
	/// Sets the weights of the connections from this layer to the next to random values in a given range.
	/// </summary>
	/// <param name="minValue">The minimum value that a weight may be set to.</param>
	/// <param name="maxValue">The minimum value that a weight may be set to.</param>
	public void SetRandomWeights (float minValue, float maxValue) {
		// Loop through all the weights associated w/ this neural layer,
		// and give them random values b/w minValue and maxValue.
		for (int i = 0; i < weights.Length; i++) {
			for (int j = 0; j < weights[i].Length; j++) {
				weights [i] [j] = UnityEngine.Random.Range (minValue, maxValue);
			}
		}
	}

	/// <summary>
	/// Returns a string that represents this layer's connection weights.
	/// </summary>
	public override string ToString() {
		string output = "";

		for (int i = 0; i < weights.Length; i++) {
			for (int j = 0; j < weights [i].Length; j++) {
				output += "[" + i + "][" + j + "]: " + weights [i] [j] + "\n";
			}
		}

		return output;
	}
	#endregion
}
