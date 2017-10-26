using System;
using System.Collections; // for collections (like IEnumerator)
using System.Collections.Generic; // for generic-typed collections
using System.IO; // for saving files
using System.Text; // for working with text in files

/// <summary>
/// Class representing one member of a population.
/// </summary>
public class Genotype : IComparable<Genotype>, IEnumerable<float> {
	#region Members
	#region Debug
	/// <summary>
	/// The index of the most-recently-created Agent.
	/// </summary>
	public static int currentGenotypeIndex = 0;

	/// <summary>
	/// The index of this agent.
	/// </summary>
	public int genotypeIndex;
	#endregion

	/// <summary>
	/// The current evaluation of this genotype.
	/// An evaluation is a raw score used to determine the fitness of a genotype.
	/// </summary>
	public float evaluation { get; set; }

	/// <summary>
	/// The current fitness of this genotype. In essence, the evaluation of this genotype as a proportion of the average evaluation of its population.
	/// </summary>
	public float fitness { get; set; }

	/// <summary>
	/// The vector of parameters of this genotype. (Parameters in a Genotype represent weights associated w/ a NeuralNetwork.)
	/// </summary>
	private float[] parameters;

	/// <summary>
	/// The number of parameters stored in the parameter vector of this genotype.
	/// </summary>
	public int parameterCount {
		get {
			if (parameters == null) {
				return 0;
			} else {
				return parameters.Length;
			}
		}
	}

	/// <summary>
	/// Overridden indexer for convenient parameter access of Genotypes.
	/// </summary>
	/// <param name="index">The index of one of this Genotype's parameters.</param>
	public float this [int index] {
		get { return parameters [index]; }
		set { parameters [index] = value; }
	}
	#endregion

	#region Constructors
	/// <summary>
	/// Creates a new genotype with a given parameter vector and initial fitness of 0.
	/// </summary>
	/// <param name="parameters">The parameter vector used to initialize this Genotype.</param>
	public Genotype (float[] parameters) {
		this.parameters = new float[parameters.Length];
		for (int i = 0; i < parameters.Length; i++) {
			this.parameters [i] = parameters [i];
		}
		fitness = 0;
		genotypeIndex = currentGenotypeIndex++;
	}
	#endregion

	#region Methods
	#region IComparable
	/// <summary>
	/// Compares this genotype with another genotype based on their fitness values.
	/// </summary>
	/// <param name="other">The genotype to compare this genotype with.</param>
	/// <returns>The result of comparing the 2 genotypes' fitnesses in reverse order.</returns>
	public int CompareTo (Genotype other) {
		// Compare fitnesses in reverse order to get larger fitness to be sorted first.
		return other.fitness.CompareTo (this.fitness);
	}
	#endregion

	#region IEnumerable
	/// <summary>
	/// Gets an Enumerator to iterate over all the parameters of this genotype.
	/// </summary>
	// This is a generic implementation of GetEnumerator().
	public IEnumerator<float> GetEnumerator () {
		for (int i = 0; i < parameters.Length; i++)
			yield return parameters [i];
	}

	/// <summary>
	/// Gets an Enumerator to iterate over all parameters of this genotype.
	/// </summary>
	// This is a non-generic implementation of GetEnumerator().
	IEnumerator IEnumerable.GetEnumerator () {
		return GetEnumerator ();
	}
	#endregion

	/// <summary>
	/// Sets the parameters of this genotype to random values in a given range.
	/// </summary>
	/// <param name="minValue">The minimum value a parameter may be initialized with.</param>
	/// <param name="maxValue">The maximum value a parameter may be initialized with.</param>
	public void SetRandomParameters (float minValue, float maxValue) {
		// Check arguments.
		if (minValue > maxValue) throw new ArgumentException ("The minimum value may not exceed the maximum value.");

		// Generate a random parameter vector by looping through each parameter,
		// giving them random values b/w minValue and maxValue.
		for (int i = 0; i < parameters.Length; i++) {
			parameters [i] = UnityEngine.Random.Range (minValue, maxValue);
		}
	}

	/// <summary>
	/// Returns a copy of the parameter vector of this Genotype.
	/// </summary>
	public float[] GetParameterCopy () {
		float[] copy = new float[parameterCount];
		for (int i = 0; i < parameterCount; i++) {
			copy [i] = parameters [i];
		}

		return copy;
	}

	/// <summary>
	/// Saves the parameters of this genotype to a file at a given file path.
	/// </summary>
	/// <param name="filePath">The path of the file to save this genotype to.</param>
	/// <remarks>This method will override existing files or attempt to create new files, if the file at the given path does not exist.</remarks>
	public void SaveToFile (string filePath) {
		// (A StringBuilder represents a MUTABLE string of characters.)
		// (strings aren't mutable in C#, hence this StringBuilder class for mutable strings.)
		StringBuilder builder = new StringBuilder ();
		foreach (float parameter in parameters) {
			// The StringBuilder class's Append () method performs better than appending strings to strings.
			// That's why we append twice here instead of appending "parameter.ToString() + ;".
			// Adding strings to strings is slow w/o the StringBuilder.Append() method!
			builder.Append (parameter.ToString ()).Append (";");
		}

		// Remove the last character (a semicolon) of 
		// the string that was made b/c it's not needed.
		builder.Remove (builder.Length - 1, 1);

		// Save the StringBuilder's string to the file located at filePath.
		File.WriteAllText (filePath, builder.ToString ());
	}

	#region Static Methods

	/// <summary>
	/// Generates a random Genotype with parameters in the given range.
	/// </summary>
	/// <returns>The random.</returns>
	/// <param name="parameterCount">The number of parameters the created Genotype consists of.</param>
	/// <param name="minValue">The minimum value a parameter may be initialized with.</param>
	/// <param name="maxValue">The maximum value a parameter may be initialized with.</param>
	/// <returns>A Genotype with random parameter values.</returns>
	public static Genotype GenerateRandom (int parameterCount, float minValue, float maxValue) {
		// Check arguments.
		if (parameterCount == 0) return new Genotype(new float[0]);

		Genotype randomGenotype = new Genotype (new float[parameterCount]);
		randomGenotype.SetRandomParameters (minValue, maxValue);

		randomGenotype.genotypeIndex = currentGenotypeIndex++;

		return randomGenotype;
	}

	/// <summary>
	/// Loads a genotype from a file with a given file path.
	/// </summary>
	/// <returns>The genotype loaded from the file at the given file path.</returns>
	/// <param name="filePath">The path of the file to load the genotype from.</param>
	public static Genotype LoadFromFile (string filePath) {
		string data = File.ReadAllText (filePath);

		List<float> parameters = new List<float> ();
		// Get an array of parsed strings that represent the loaded Genotype's parameter (weight) values.
		string[] paramStrings = data.Split (';');

		foreach (string parameter in paramStrings) {
			float result;
			// If result == 0, then TryParse() failed.
			// C# considers 0 to be false when converting numbers to booleans.
			// Try to parse each parameter to a float.
			// If parsing succeeds, add the parsed float to the parameters list.
			if (!float.TryParse (parameter, out result)) {
				throw new ArgumentException ("The file at the given file path does not contain a valid genotype serialization.");
			} else {
				parameters.Add (result);
			}
		}

		// Return a Genotype created from the parameters list-converted-to-array.
		return new Genotype (parameters.ToArray ());;
	}
	#endregion
	#endregion
}
