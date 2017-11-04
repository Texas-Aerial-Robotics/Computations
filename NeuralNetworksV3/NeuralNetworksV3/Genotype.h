#pragma once
#include <vector>
class Genotype
{

#pragma region Fields
public:
	/*#region Debug
	/// <summary>
	/// The index of the most-recently-created Agent.
	/// </summary>
	public static int currentGenotypeIndex = 0;

	/// <summary>
	/// The index of this agent.
	/// </summary>
	public int genotypeIndex;
	#endregion
	*/

	/// <summary>
	/// The current evaluation of this genotype.
	/// An evaluation is a raw score used to determine the fitness of a genotype.
	/// </summary>
	float evaluation;

	/// <summary>
	/// The current fitness of this genotype. In essence, the evaluation of this genotype as a proportion of the average evaluation of its population.
	/// </summary>
	float fitness;

private:
	/// <summary>
	/// The vector of parameters of this genotype. (Parameters in a Genotype represent weights associated w/ a NeuralNetwork.)
	/// </summary>
	std::vector<float> parameters;

	/// <summary>
	/// The number of parameters stored in the parameter vector of this genotype.
	/// </summary>
	int parameterCount;
#pragma endregion

#pragma region Constructors
public:
	/// <summary>
	/// Creates a new genotype with a given parameter vector and initial fitness of 0.
	/// </summary>
	/// <param name="_parameters">The parameter vector used to initialize this Genotype.</param>
	Genotype(std::vector<float> _parameters);

	~Genotype();

	/// <summary>
	/// Just a default constructor. Isn't used for anything except for raw Genotype declarations.
	/// </summary>
	Genotype();
#pragma endregion

#pragma region Methods
public:
#pragma region Get/Set
	/// <summary>
	/// Gets the parameterCount of this Genotype.
	/// </summary>
	int GetParameterCount();

	/// <summary>
	/// Gets the parameter at index in the parameters vector.
	/// </summary>
	/// <param name="index">The index of one of this Genotype's parameters.</param>
	float GetParameter(int index);

	/// <summary>
	/// Sets the parameter at index in the parameters vector to value.
	/// </summary>
	/// <param name="index">The index of one of this Genotype's parameters.</param>
	/// <param name="value">The value that parameters[index] will take.</param>
	void SetParameter(int index, float value);
#pragma endregion
	/*
	/// <summary>
	/// Compares this genotype with another genotype based on their fitness values.
	/// </summary>
	/// <param name="other">The genotype to compare this genotype with.</param>
	/// <returns>The result of comparing the 2 genotypes' fitnesses in descending order.</returns>
	int CompareTo(Genotype other) {
	// Compare fitnesses in reverse (descending) order to get larger fitness to be sorted first.
	return other.fitness - fitness;
	}*/

	/*#region IEnumerable
	/// <summary>
	/// Gets an Enumerator to iterate over all the parameters of this genotype.
	/// </summary>
	// This is a generic implementation of GetEnumerator().
	public IEnumerator<float> GetEnumerator() {
	for (int i = 0; i < parameters.Length; i++)
	yield return parameters[i];
	}

	/// <summary>
	/// Gets an Enumerator to iterate over all parameters of this genotype.
	/// </summary>
	// This is a non-generic implementation of GetEnumerator().
	IEnumerator IEnumerable.GetEnumerator() {
	return GetEnumerator();
	}
	#endregion*/

	/// <summary>
	/// Sets the parameters of this genotype to random values in a given range.
	/// </summary>
	/// <param name="minValue">The minimum value a parameter may be initialized with.</param>
	/// <param name="maxValue">The maximum value a parameter may be initialized with.</param>
	void SetRandomParameters(float minValue, float maxValue);

	/// <summary>
	/// Returns a copy of the parameter vector of this Genotype.
	/// </summary>
	std::vector<float> GetParameterCopy();

	// TODO: Add support for saving/loading genotypes.
	/*
	/// <summary>
	/// Saves the parameters of this genotype to a file at a given file path.
	/// </summary>
	/// <param name="filePath">The path of the file to save this genotype to.</param>
	/// <remarks>This method will override existing files or attempt to create new files, if the file at the given path does not exist.</remarks>
	void SaveToFile(std::string filePath) {
		std::string parameterString = "";
		for (int i = 0; i < parameters.size; i++) {
			// The StringBuilder class's Append () method performs better than appending strings to strings.
			// That's why we append twice here instead of appending "parameter.ToString() + ;".
			// Adding strings to strings is slow w/o the StringBuilder.Append() method!
			parameterString += parameters[i].ToString() + ";";
		}

		// Remove the last character (a semicolon) of 
		// the string that was made b/c it's not needed.
		parameterString.pop_back();

		// TODO:
		// Save the StringBuilder's string to the file located at filePath.
		// File.WriteAllText(filePath, builder.ToString());
	}
	*/

#pragma region Static Methods
	/// <summary>
	/// Generates a random Genotype with parameters in the given range.
	/// </summary>
	/// <returns>The random.</returns>
	/// <param name="parameterCount">The number of parameters the created Genotype consists of.</param>
	/// <param name="minValue">The minimum value a parameter may be initialized with.</param>
	/// <param name="maxValue">The maximum value a parameter may be initialized with.</param>
	/// <returns>A Genotype with random parameter values.</returns>
	static Genotype GenerateRandom(int parameterCount, float minValue, float maxValue);

	// TODO: Add support for saving/loading genotypes.
	/*
	/// <summary>
	/// Loads a genotype from a file with a given file path.
	/// </summary>
	/// <returns>The genotype loaded from the file at the given file path.</returns>
	/// <param name="filePath">The path of the file to load the genotype from.</param>
	static Genotype LoadFromFile(std::string filePath) {
		std::string data = File.ReadAllText(filePath);

		List<float> parameters = new List<float>();
		// Get an array of parsed strings that represent the loaded Genotype's parameter (weight) values.
		std::vector<std::string> paramStrings;
		
		// TODO: convert string from file into list of parameters using semicolons as delimiters.
		= data.Split(';');

		std::vector<float> parameters; parameters.reserve(paramStrings.size);

		for (int i = 0; i < paramStrings.size; i++) {
			float result;
			// If result == 0, then TryParse() failed.
			// C# considers 0 to be false when converting numbers to booleans.
			// Try to parse each parameter to a float.
			// If parsing succeeds, add the parsed float to the parameters list.
			if (!float.TryParse(parameter, out result)) {
				throw new ArgumentException("The file at the given file path does not contain a valid genotype serialization.");
			}
			else {
				parameters.Add(result);
			}
		}

		// Return a Genotype created from the parameters list-converted-to-array.
		return new Genotype(parameters.ToArray());
	}*/
#pragma endregion
#pragma endregion
};
