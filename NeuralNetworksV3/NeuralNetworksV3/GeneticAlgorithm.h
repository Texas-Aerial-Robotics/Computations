#pragma once
#include "Genotype.h"
#include <vector>
class GeneticAlgorithm
{

	// TODO: Make sure that genotypes are sorted in ascending order by using std::sort (vector.start, vector.end, std::greater<int>()).
	// (Don't just use std::sort(vector.start, vector.end)
public:
	GeneticAlgorithm();
	~GeneticAlgorithm();

#pragma region Fields
#pragma region Default Parameters
public:
	/// <summary>
	/// The default min value of initial population parameters.
	/// </summary>
	const float defInitParamMin = -1.0f;

	/// <summary>
	/// The default max value of initial population parameters.
	/// </summary>
	const float defInitParamMax = 1.0f;

	/// <summary>
	/// The default probability of a parameter being swapped during crossover.
	/// </summary>
	const float defCrossSwapProb = 0.6f;

	/// <summary>
	/// The default probability of a parameter being mutated.
	/// </summary>
	const float defMutationProb = .3f;

	/// <summary>
	/// The default amount by which parameters may be mutated.
	/// </summary>
	const float defMutationAmount = 2.0f;

	/// <summary>
	/// The default proportion of genotypes in a new population that are mutated.
	/// </summary>
	const float defMutationPerc = 1.0f;
	#pragma endregion

// TODO: Wire the correct methods to the below function pointers.
#pragma region Operator Function Pointers
	/// <summary>
	/// Function pointer used to initialize the initial population.
	/// </summary>
	/// <param name="initialPopulation">The population to be initialized.</param> 
	void (*InitializePopulation)(std::vector<Genotype> initialPopulation) = NULL;

	/// <summary>
	/// Function pointer used to load genotypes into the initial population.
	/// </summary>
	/// <param name="initialPopulation">The population to load genotypes into.</param>
	void (*GenotypeLoadingMethod)(std::vector<Genotype> initialPopulation) = NULL;

	/// <summary>
	/// Function pointer used to save genotypes found in a final population.
	/// </summary>
	void (*GenotypeSavingMethod)(std::vector<Genotype> finalPopulation) = NULL;

	/// <summary>
	/// Function pointer used to evaluate (or start the evaluation process of) the current population.
	/// </summary>
	/// <param name="currentPopulation">The current population.</param>
	void (*Evaluation)(std::vector<Genotype> currentPopulation) = NULL;

	/// <summary>
	/// Function pointer used to calculate the fitness value of each genotype of the current population.
	/// </summary>
	void (*FitnessCalculation)(std::vector<Genotype> currentPopulation) = NULL;

	/// <summary>
	/// Function pointer used to select genotypes of the current population and create an intermediate population.
	/// </summary>
	/// <param name="currentPopulation">The current population.</param> 
	/// <returns>The intermediate population.</returns>
	std::vector<Genotype> (*SelectionOperator)(std::vector<Genotype> currentPopulation) = NULL;

	/// <summary>
	/// Function pointer used to recombine a intermediate population to generate a new population.
	/// </summary>
	/// <param name="intermediatePopulation">The intermediate population.</param>
	/// <returns>The new population.</returns>
	std::vector<Genotype> (*RecombinationOperator)(std::vector<Genotype> intermediatePopulation, int newPopulationSize) = NULL;

	/// <summary>
	/// Function pointer used to mutate a new population.
	/// </summary>
	void (*MutationOperator)(std::vector<Genotype> newPopulation) = NULL;

	/// <summary>
	/// Function pointer used to check whether any termination criterion has been met.
	/// </summary>
	bool (*CheckTerminationCriteria)(std::vector<Genotype> currentPopulation) = NULL;
	#pragma endregion

	/*#pragma region Operator Methods
	/// <summary>
	/// Method used to initialize an initial population.
	/// </summary>
	InitializationOperator InitializePopulation = DefaultPopulationInitialization;

	/// <summary>
	/// Method used to load genotypes into an initial population.
	/// </summary>
	public GenotypeLoadingOperator GenotypeLoadingMethod;

	/// <summary>
	/// Method used to save genotypes found in a final population.
	/// </summary>
	public GenotypeSavingOperator GenotypeSavingMethod;

	/// <summary>
	/// Method used to evaluate (or start the evaluation process of) the current population.
	/// </summary>
	public EvaluationOperator Evaluation;

	/// <summary>
	/// Method used to calculate the fitness value of each genotype in the current population.
	/// </summary>
	public FitnessCalculation FitnessCalculationMethod = DefaultFitnessCalculation;

	/// <summary>
	/// Method used to select genotypes of the current population and create an intermediate population.
	/// </summary>
	public SelectionOperator Selection = DefaultSelectionOperator;

	/// <summary>
	/// Method used to recombine an intermediate population to generate a new population.
	/// </summary>
	public RecombinationOperator Recombination = DefaultRecombinationOperator;

	/// <summary>
	/// Method used to mutate a new population.
	/// </summary>
	public MutationOperator Mutation = DefaultMutationOperator;

	/// <summary>
	/// Method used to check whether any termination criterion has been met.
	/// </summary>
	public CheckTerminationCriteria TerminationCriteria = null;
	#pragma endregion
	*/

private:
	/// <summary>
	/// The current population.
	/// </summary>
	std::vector<Genotype> currentPopulation;

public:
	/// <summary>
	/// The number of genotypes in a population.
	/// </summary>
	int populationSize;

	/// <summary>
	/// The number of generations that have already passed.
	/// </summary>
	int generationCount;

	/// <summary>
	/// Whether the current population will be sorted before calling the termination criteria operator.
	/// </summary>
	bool sortPopulation;

	/// <summary>
	/// Whether this genetic algorithm is currently running.
	/// </summary>
	bool running;

	/// <summary>
	/// Event for when this algorithm is eventually terminated.
	/// </summary>
	void (*AlgorithmTerminated)(GeneticAlgorithm ga);

	/// <summary>
	/// Event for when this algorithm has finished a fitness calculation. The given parameter
	/// is the current population sorted by fitness, if sorting is enabled (see <see cref="SortPopulation"/>).
	/// </summary>
	void (*FitnessCalculationFinished)(std::vector<Genotype> genotypes);
	#pragma endregion

#pragma region Constructors
	public:
	/// <summary>
	/// Initializes a new genetic algorithm instance, creating an initial population of given size with genotypes
	/// of a given parameter count.
	/// </summary>
	/// <param name="genotypeParamCount">The number of parameters per genotype.</param>
	/// <param name="populationSize">The size of the population.</param>
	GeneticAlgorithm(int genotypeParamCount, int _populationSize) {
		populationSize = _populationSize;

		// Initialize an empty population.
		std::vector<Genotype> currentPopulation; currentPopulation.reserve(populationSize);
		// Add new genotypes to the population.
		for (int i = 0; i < populationSize; i++) {
			std::vector<float> currentParameterVector; currentParameterVector.reserve(genotypeParamCount); // a vector that will store the parameters of the current genotype
			currentPopulation[i] = Genotype(currentParameterVector);
		}

		generationCount = 1;
		sortPopulation = true;
		running = false;
	}
#pragma endregion

#pragma region Methods
	public:
		void Start() {
		running = true;

		InitializePopulation(currentPopulation);

		// Load Genotypes into the current population if GenotypeLoadingMethod is not null.
		if (GenotypeLoadingMethod != NULL)
			GenotypeLoadingMethod(currentPopulation);

		Evaluation(currentPopulation);
	}

	/// <summary>
	/// Evaluates a population after it has run its course.
	/// </summary>
	public void EvaluationFinished() {
		// Calcuate a fitness from a recently-ended evaluation.
		FitnessCalculationMethod(currentPopulation);

		// Sort the population if sortPopulation is true.
		if (sortPopulation)
			currentPopulation.Sort();

		// Create a string that debugs information about the last evaluation.
		string evalString = "Worst evaluation: " + currentPopulation[populationSize - 1].evaluation + "\n";

		if (currentPopulation[0].evaluation == 0)
			evalString += "Problem!\n" + currentPopulation[1].evaluation;
		else
			evalString += "Best evaluation: " + currentPopulation[0].evaluation + " (Genotype " + currentPopulation[0].genotypeIndex + ")";

		Debug.Log(evalString);

		// Fire the FitnessCalculationFinished event if it's not null.
		if (FitnessCalculationFinished != null)
			FitnessCalculationFinished(currentPopulation);

		// Check termination criteria, and terminate this GeneticAlgorithm if TerminationCriteria() returns true.
		// (This is an example of shortcircuit evaluation!)
		if (TerminationCriteria != null && TerminationCriteria(currentPopulation)) {
			Terminate();
			return;
		}

		// Now create a new population!
		CreateNewPopulation();
		Evaluation(currentPopulation);
	}

	/// <summary>
	/// Creates a new population of genotypes, and increments generationCount by 1.
	/// (Assumes that currentPopulation has been sorted.)
	/// </summary>
	private void CreateNewPopulation() {
		// Apply the Selection method.
		std::vector<Genotype> intermediatePopulation = Selection(currentPopulation);

		// Apply the Recombination method.
		std::vector<Genotype> newPopulation = Recombination(intermediatePopulation, populationSize);

		// Apply the Mutation method.
		Mutation(newPopulation);

		// Set the current population to a newly generated one, and start evaluation again.
		currentPopulation = newPopulation;
		generationCount++;
	}

	/// <summary>
	/// Terminates this GeneticAlgorithm.
	/// </summary>
	private void Terminate() {
		running = false;

		// Save genotypes from currentPopulation if GenotypeSavingMethod is defined.
		if (GenotypeSavingMethod != null)
			GenotypeSavingMethod(currentPopulation);

		// Call AlgorithmTerminated if it's not null.
		if (AlgorithmTerminated != null) {
			AlgorithmTerminated(this);
		}
	}

#pragma region Static Methods
#pragma region Default Operators
		/// <summary>
		/// Initializes the population by setting each parameter in each genotype to a random value in a default range.
		/// </summary>
		/// <param name="population">The population to be initialized.</param>
		public static void DefaultPopulationInitialization(std::vector<Genotype> population) {
		// Set parameters to random values in a set range.
		foreach(Genotype genotype in population) {
			genotype.SetRandomParameters(defInitParamMin, defInitParamMax);
		}
	}

	/// <summary>
	/// Calculates the fitness of each genotype by the formula: fitness = evaluation / averageEvaluation.
	/// </summary>
	/// <param name="currentPopulation">The current population.</param>
	public static void DefaultFitnessCalculation(std::vector<Genotype> currentPopulation) {
		// First calculate the average evaluation of the whole population.
		int currentPopulationSize = 0;
		float totalEvaluation = 0;
		foreach(Genotype genotype in currentPopulation) {
			totalEvaluation += genotype.evaluation;
			currentPopulationSize++;
		}

		float averageEvaluation = totalEvaluation / currentPopulationSize;

		// Assign fitnesses with the formula: fitness = evaluation / averageEvaluation.
		foreach(Genotype genotype in currentPopulation) {
			genotype.fitness = genotype.evaluation / averageEvaluation;
		}
	}

	/// <summary>
	/// Only selects the best 3 genotypes of the current population, and copies them to an intermediate population.
	/// </summary>
	/// <returns>An intermediate population.</returns>
	/// <param name="currentPopulation">The current population.</param>
	public static std::vector<Genotype> DefaultSelectionOperator(std::vector<Genotype> currentPopulation) {
		// Check arguments
		if (currentPopulation.Count < 3) {
			throw new ArgumentException("The current population must have at least 3 genotypes for this selection operator to work!");
		}

		std::vector<Genotype> intermediatePopulation = new std::vector<Genotype>();
		intermediatePopulation.Add(currentPopulation[0]);
		intermediatePopulation.Add(currentPopulation[1]);
		intermediatePopulation.Add(currentPopulation[2]);

		return intermediatePopulation;
	}

	/// <summary>
	/// Simply crosses the first genotype of the intermediate population with the second genotype of the intermediate 
	/// population until the new population is of a given desired size.
	/// </summary>
	/// <returns>A new population.</returns>
	/// <param name="intermediatePopulation">The intermediate population that was created from the selection process.</param>
	/// <param name="newPopulationSize">The size of the new population.</param>
	public static std::vector<Genotype> DefaultRecombinationOperator(std::vector<Genotype> intermediatePopulation, int newPopulationSize) {
		// Check arguments.
		if (intermediatePopulation.Count < 2)
			throw new ArgumentException("The intermediate population size must be at least 2 for this operator.");

		if (newPopulationSize < 2)
			throw new ArgumentException("The new population size must be at least 2 for this operator.");

		std::vector<Genotype> newPopulation = new std::vector<Genotype>();

		newPopulation.Add(intermediatePopulation[0]);
		newPopulation.Add(intermediatePopulation[1]);

		// Add new Genotypes to the population until there are newPopulationSize Genotypes in the population.
		while (newPopulation.Count < newPopulationSize) {
			Genotype offspring1, offspring2;
			CompleteCrossover(intermediatePopulation[0], intermediatePopulation[1], defCrossSwapProb, out offspring1, out offspring2);

			newPopulation.Add(offspring1);
			// Don't add another Genotype to the population if there isn't room for another Genotype.
			if (newPopulation.Count < newPopulationSize)
				newPopulation.Add(offspring2);
		}

		return newPopulation;
	}

	/// <summary>
	/// Simply mutates each genotype with the default mutation probability and amount.
	/// </summary>
	/// <param name="newPopulation">A new, mutated population.</param>
	public static void DefaultMutationOperator(std::vector<Genotype> newPopulation) {
		foreach(Genotype genotype in newPopulation) {
			// Mutate approximately defMutationPerc of genotypes in the population.
			if (UnityEngine.Random.Range(0f, 1f) < defMutationPerc)
				MutateGenotype(genotype, defMutationProb, defMutationAmount);
		}
	}
#pragma endregion

#pragma region Recombination Operators
	/// <summary>
	/// Gives offspring genotypes parameters from their respective parent genotypes, swapping the parents from which offspring get parameters based on swapChance.
	/// </summary>
	public static void CompleteCrossover(Genotype parent1, Genotype parent2, float swapChance, out Genotype offspring1, out Genotype offspring2) {
		// Initialize new parameter vectors.
		int parameterCount = parent1.parameterCount;

		// off1Parameters is an array of floats representing offspring1's parameters.
		float[] off1Parameters = new float[parameterCount], off2Parameters = new float[parameterCount];

		// Iterate over all of the parents' parameters, giving parameters from parents to their respective offspring.
		for (int i = 0; i < parameterCount; i++) {
			if (UnityEngine.Random.Range(0f, 1f) < swapChance) {
				// Swap parent-to-offspring parameters.
				off1Parameters[i] = parent2[i];
				off2Parameters[i] = parent1[i];
			}
			else {
				// Don't swap parent-to-offspring parameters.
				off1Parameters[i] = parent1[i];
				off2Parameters[i] = parent2[i];
			}
		}

		offspring1 = new Genotype(off1Parameters);
		offspring2 = new Genotype(off2Parameters);
	}
#pragma endregion

#pragma region Mutation Operators
	/// <summary>
	/// Mutates a given genotype by adding a random value in the range [-mutationAmount, mutationAmount] to each parameter with a probability of mutationProb.
	/// </summary>
	/// <param name="genotype">The genotype to be mutated.</param>
	/// <param name="mutationProb">The probability of a parameter being mutated.</param>
	/// <param name="mutationAmount">A parameter may be mutated by an amount in the range [-mutationAmount, mutationAmount].</param>
	public static void MutateGenotype(Genotype genotype, float mutationProb, float mutationAmount) {
		for (int i = 0; i < genotype.parameterCount; i++) {
			if (UnityEngine.Random.Range(0f, 1f) < mutationProb) {
				// Mutate by a random amount in the range [-mutationAmount, mutationAmount].
				genotype[i] += UnityEngine.Random.Range(-1f, 1f) * mutationAmount;
			}
		}
	}
#pragma endregion
#pragma endregion
#pragma endregion
};

