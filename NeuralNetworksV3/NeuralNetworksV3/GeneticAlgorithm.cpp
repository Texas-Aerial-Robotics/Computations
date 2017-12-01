#include "stdafx.h"
#include <algorithm> // for std::sort
#include <functional> // for std::greater
#include "MathHelper.h"
#include "GeneticAlgorithm.h"

#pragma region Fields
#pragma region Default Parameters
const float GeneticAlgorithm::defInitParamMin = -1.0f;

const float GeneticAlgorithm::defInitParamMax = 1.0f;

const float GeneticAlgorithm::defCrossSwapProb = 0.6f;

const float GeneticAlgorithm::defMutationProb = .3f;

const float GeneticAlgorithm::defMutationAmount = 2.0f;

const float GeneticAlgorithm::defMutationProp = 1.0f;
#pragma endregion
#pragma endregion

#pragma region Methods
#pragma region Operator Functions
#pragma endregion

#pragma General
GeneticAlgorithm::GeneticAlgorithm()
{
}

void GeneticAlgorithm::Start() {
	running = true;

	InitializePopulation(currentPopulation);

	// Load Genotypes into the current population if GenotypeLoadingMethod is not null.
	if (GenotypeLoadingMethod != nullptr)
		GenotypeLoadingMethod(currentPopulation);

	Evaluation(currentPopulation);
}

void GeneticAlgorithm::EvaluationFinished() {
	// Calcuate a fitness from a recently-ended evaluation.
	FitnessCalculationMethod(currentPopulation);

	struct greater
	{
		bool operator()(Genotype const &a, Genotype const &b) const { return a.evaluation > b.evaluation; }
	};

	// Sort the population if sortPopulation is true.
	if (sortPopulation) {
		//std::sort(currentPopulation.begin, currentPopulation.end, std::greater<int>())();
		std::sort(currentPopulation.begin(), currentPopulation.end(), greater());
	}

	/*
	// Create a string that debugs information about the last evaluation.
	std::string evalString = "Worst evaluation: " + currentPopulation[populationSize - 1].evaluation + "\n";

	if (currentPopulation[0].evaluation == 0)
		evalString += "Problem!\n" + currentPopulation[1].evaluation;
	else
		evalString += "Best evaluation: " + currentPopulation[0].evaluation + " (Genotype " + currentPopulation[0].genotypeIndex + ")";

	Debug.Log(evalString);
	*/

	// Fire the FitnessCalculationFinished event if it's not null.
	if (FitnessCalculationFinished != NULL)
		FitnessCalculationFinished(currentPopulation);

	// Check termination criteria, and terminate this GeneticAlgorithm if TerminationCriteria() returns true.
	// (This is an example of shortcircuit evaluation!)
	if (CheckTerminationCriteria != NULL && CheckTerminationCriteria(currentPopulation)) {
		Terminate();
		return;
	}

	// Now create a new population!
	CreateNewPopulation();
	Evaluation(currentPopulation);
}

void GeneticAlgorithm::CreateNewPopulation() {
	// Apply the Selection method.
	std::vector<Genotype> intermediatePopulation = SelectionOperator(currentPopulation);

	// Apply the Recombination method.
	std::vector<Genotype> newPopulation = RecombinationOperator(intermediatePopulation, populationSize);

	// Apply the Mutation method.
	MutationOperator(newPopulation);

	// Set the current population to a newly generated one, and start evaluation again.
	currentPopulation = newPopulation;
	generationCount++;
}

void GeneticAlgorithm::Terminate() {
	running = false;

	// Save genotypes from currentPopulation if GenotypeSavingMethod is defined.
	if (GenotypeSavingMethod != NULL)
		GenotypeSavingMethod(currentPopulation);

	// Call AlgorithmTerminated if it's not null.
	if (AlgorithmTerminated != NULL) {
		AlgorithmTerminated(*this);
	}
}
#pragma endregion

#pragma region Static Methods
#pragma region Default Operators
	void GeneticAlgorithm::InitializePopulation(std::vector<Genotype> population) {
		// Set parameters to random values in a set range.
		for (size_t i = 0; i < population.size(); i++) {
			population[i].SetRandomParameters(defInitParamMin, defInitParamMax);
		}
	}

	/// <summary>
	/// Calculates the fitness of each genotype by the formula: fitness = evaluation / averageEvaluation.
	/// </summary>
	/// <param name="currentPopulation">The current population.</param>
	void GeneticAlgorithm::DefaultFitnessCalculation(std::vector<Genotype> currentPopulation) {
		// First calculate the average evaluation of the whole population.
		int currentPopulationSize = 0;
		float totalEvaluation = 0;
		for (size_t i = 0; i < currentPopulation.size(); i++) {
			totalEvaluation += currentPopulation[i].evaluation;
			currentPopulationSize++;
		}

		float averageEvaluation = totalEvaluation / currentPopulationSize;

		// Assign fitnesses with the formula: fitness = evaluation / averageEvaluation.
		for (size_t i = 0; i < currentPopulation.size(); i++) {
			currentPopulation[i].fitness = currentPopulation[i].evaluation / averageEvaluation;
		}
	}

	/// <summary>
	/// Only selects the best 3 genotypes of the current population, and copies them to an intermediate population.
	/// </summary>
	/// <returns>An intermediate population.</returns>
	/// <param name="currentPopulation">The current population.</param>
	std::vector<Genotype> GeneticAlgorithm::DefaultSelectionOperator(std::vector<Genotype> currentPopulation) {
		// Check arguments
		if (currentPopulation.size() < 3) {
			throw new std::invalid_argument("The current population must have at least 3 genotypes for this selection operator to work!");
		}

		std::vector<Genotype> intermediatePopulation; intermediatePopulation.reserve(3);
		intermediatePopulation[0] = currentPopulation[0];
		intermediatePopulation[1] = currentPopulation[1];
		intermediatePopulation[2] = currentPopulation[2];

		return intermediatePopulation;
	}

	/// <summary>
	/// Simply crosses the first genotype of the intermediate population with the second genotype of the intermediate 
	/// population until the new population is of a given desired size.
	/// </summary>
	/// <returns>A new population.</returns>
	/// <param name="intermediatePopulation">The intermediate population that was created from the selection process.</param>
	/// <param name="newPopulationSize">The size of the new population.</param>
	std::vector<Genotype> GeneticAlgorithm::DefaultRecombinationOperator(std::vector<Genotype> intermediatePopulation, unsigned int newPopulationSize) {
		// Check arguments.
		if (intermediatePopulation.size() < 2)
			throw new std::invalid_argument("The intermediate population size must be at least 2 for this operator.");

		if (newPopulationSize < 2)
			throw new std::invalid_argument("The new population size must be at least 2 for this operator.");

		std::vector<Genotype> newPopulation; newPopulation.reserve(newPopulationSize);

		// Add first 2 genotypes of intermediatePopulation to newPopulation.
		newPopulation[newPopulation.size()] = intermediatePopulation[0];
		newPopulation[newPopulation.size()] = intermediatePopulation[1];

		// Add new Genotypes to the population until there are newPopulationSize Genotypes in the population.
		while (newPopulation.size() < newPopulationSize) {
			Genotype offspring1 = Genotype();
			Genotype offspring2 = Genotype();
			CompleteCrossover(intermediatePopulation[0], intermediatePopulation[1], defCrossSwapProb, offspring1, offspring2);

			newPopulation[newPopulation.size()] = offspring1;
			// Don't add another Genotype to the population if there isn't room for another Genotype.
			if (newPopulation.size() < newPopulationSize)
				newPopulation[newPopulation.size()] = offspring2;
		}

		return newPopulation;
	}

	/// <summary>
	/// Simply mutates each genotype with the default mutation probability and amount.
	/// </summary>
	/// <param name="newPopulation">A new, mutated population.</param>
	void GeneticAlgorithm::DefaultMutationOperator(std::vector<Genotype> newPopulation) {
		for (unsigned int i = 0; i < newPopulation.size(); i++) {
			// Mutate approximately defMutationPerc of genotypes in the population.
			if (MathHelper::RandomRange(0.f, 1.f) < defMutationProp) {
				MutateGenotype(newPopulation[i], defMutationProb, defMutationAmount);
			}
		}
	}
#pragma endregion

#pragma region Recombination Operators
	/// <summary>
	/// Gives offspring genotypes parameters from their respective parent genotypes, swapping the parents from which offspring get parameters based on swapChance.
	/// </summary>
	void GeneticAlgorithm::CompleteCrossover(Genotype parent1, Genotype parent2, float swapChance, Genotype& offspring1, Genotype& offspring2) {
		// Initialize new parameter vectors.
		int parameterCount = parent1.GetParameterCount();

		// off1Parameters is an array of floats representing offspring1's parameters.
		std::vector<float> off1Parameters; off1Parameters.reserve(parameterCount);
		std::vector<float> off2Parameters; off2Parameters.reserve(parameterCount);

		// Iterate over all of the parents' parameters, giving parameters from parents to their respective offspring.
		for (int i = 0; i < parameterCount; i++) {
			if (MathHelper::RandomRange(0.f, 1.f) < swapChance) {
				// Swap parent-to-offspring parameters.
				off1Parameters[i] = parent2.GetParameter(i);
				off2Parameters[i] = parent1.GetParameter(i);
			}
			else {
				// Don't swap parent-to-offspring parameters.
				off1Parameters[i] = parent1.GetParameter(i);
				off2Parameters[i] = parent2.GetParameter(i);
			}
		}

		offspring1 = Genotype(off1Parameters);
		offspring2 = Genotype(off2Parameters);
	}
#pragma endregion

#pragma region Mutation Operators
	void GeneticAlgorithm::MutateGenotype(Genotype &genotype, float mutationProb, float mutationAmount) {
		for (int i = 0; i < genotype.GetParameterCount(); i++) {
			if (MathHelper::RandomRange(0.f, 1.f) < mutationProb) {
				// Mutate by a random amount in the range [-mutationAmount, mutationAmount].
				genotype.SetParameter(i, (genotype.GetParameter(i) + MathHelper::RandomRange(-1.f, 1.f) * mutationAmount));
			}
		}


	}
#pragma endregion
#pragma endregion
#pragma endregion
