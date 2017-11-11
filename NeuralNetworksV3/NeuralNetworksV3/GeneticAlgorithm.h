#pragma once
#include "Genotype.h"
#include <vector>

//TODO: Add the MathHelper class. Add a RandomRange (min, max) function to the MathHelper class.
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
	static const float defInitParamMin;

	/// <summary>
	/// The default max value of initial population parameters.
	/// </summary>
	static const float defInitParamMax;

	/// <summary>
	/// The default probability of a parameter being swapped during crossover.
	/// </summary>
	static const float defCrossSwapProb;

	/// <summary>
	/// The default probability of a parameter being mutated.
	/// </summary>
	static const float defMutationProb;

	/// <summary>
	/// The default amount by which parameters may be mutated.
	/// </summary>
	static const float defMutationAmount;

	/// <summary>
	/// The default proportion of genotypes in a new population that are mutated.
	/// </summary>
	static const float defMutationProp;
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
	void (*FitnessCalculationMethod)(std::vector<Genotype> currentPopulation) = NULL;

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
	std::vector<Genotype> (*RecombinationOperator)(std::vector<Genotype> intermediatePopulation, unsigned int newPopulationSize) = NULL;

	/// <summary>
	/// Function pointer used to mutate a new population.
	/// </summary>
	void (*MutationOperator)(std::vector<Genotype> newPopulation) = NULL;

	/// <summary>
	/// Function pointer used to check whether any termination criterion has been met.
	/// </summary>
	bool (*CheckTerminationCriteria)(std::vector<Genotype> currentPopulation) = NULL;
	#pragma endregion

#pragma region General
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
	void (*AlgorithmTerminated)(GeneticAlgorithm ga) = NULL;

	/// <summary>
	/// Event for when this algorithm has finished a fitness calculation. The given parameter
	/// is the current population sorted by fitness, if sorting is enabled (see <see cref="SortPopulation"/>).
	/// </summary>
	void (*FitnessCalculationFinished)(std::vector<Genotype> genotypes) = NULL;
#pragma endregion
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
	void Start();

	/// <summary>
	/// Evaluates a population after it has run its course.
	/// </summary>
	void EvaluationFinished();

private:
	/// <summary>
	/// Creates a new population of genotypes, and increments generationCount by 1.
	/// (Assumes that currentPopulation has been sorted.)
	/// </summary>
	void CreateNewPopulation();

	/// <summary>
	/// Terminates this GeneticAlgorithm.
	/// </summary>
	void Terminate();

#pragma region Static Methods
#pragma region Default Operators
public:
	/// <summary>
	/// Initializes the population by setting each parameter in each genotype to a random value in a default range.
	/// </summary>
	/// <param name="population">The population to be initialized.</param>
	static void DefaultPopulationInitialization(std::vector<Genotype> population);

	/// <summary>
	/// Calculates the fitness of each genotype by the formula: fitness = evaluation / averageEvaluation.
	/// </summary>
	/// <param name="currentPopulation">The current population.</param>
	static void DefaultFitnessCalculation(std::vector<Genotype> currentPopulation);

	/// <summary>
	/// Only selects the best 3 genotypes of the current population, and copies them to an intermediate population.
	/// </summary>
	/// <returns>An intermediate population.</returns>
	/// <param name="currentPopulation">The current population.</param>
	static std::vector<Genotype> DefaultSelectionOperator(std::vector<Genotype> currentPopulation);

	/// <summary>
	/// Simply crosses the first genotype of the intermediate population with the second genotype of the intermediate 
	/// population until the new population is of a given desired size.
	/// </summary>
	/// <returns>A new population.</returns>
	/// <param name="intermediatePopulation">The intermediate population that was created from the selection process.</param>
	/// <param name="newPopulationSize">The size of the new population.</param>
	static std::vector<Genotype> DefaultRecombinationOperator(std::vector<Genotype> intermediatePopulation, unsigned int newPopulationSize);

	/// <summary>
	/// Simply mutates each genotype with the default mutation probability and amount.
	/// </summary>
	/// <param name="newPopulation">A new, mutated population.</param>
	static void DefaultMutationOperator(std::vector<Genotype> newPopulation);
#pragma endregion

#pragma region Recombination Operators
public:
	/// <summary>
	/// Gives offspring genotypes parameters from their respective parent genotypes, swapping the parents from which offspring get parameters based on swapChance.
	/// </summary>
	static void CompleteCrossover(Genotype parent1, Genotype parent2, float swapChance, Genotype& offspring1, Genotype& offspring2);
#pragma endregion

#pragma region Mutation Operators
public:
	/// <summary>
	/// Mutates a given genotype by adding a random value in the range [-mutationAmount, mutationAmount] to each parameter with a probability of mutationProb.
	/// </summary>
	/// <param name="genotype">The genotype to be mutated.</param>
	/// <param name="mutationProb">The probability of a parameter being mutated.</param>
	/// <param name="mutationAmount">A parameter may be mutated by an amount in the range [-mutationAmount, mutationAmount].</param>
	static void MutateGenotype(Genotype &genotype, float mutationProb, float mutationAmount);
#pragma endregion
#pragma endregion
#pragma endregion
};

