#pragma once
#include "GeneticAlgorithm.h"
#include "Agent.h"
#include "NeuralNetwork.h"
#include <vector>
#include <math.h> // For std math functions
#include "MathHelper.h" // custom math functions

/// <summary>
/// Singleton class for managing the adaptation process.
/// </summary>
class GeneticsManager {
#pragma region Fields
public:
	/// <summary>
	/// The one and only GeneticsManager instance.
	/// </summary>
	static GeneticsManager instance;

	/// <summary>
	/// Whether the GeneticsManager instance has been created.
	/// </summary>
	static bool instanceCreated;

private:
	// Whether or not the results of each generation shall be written to a file; to be set in some UI.
	bool saveStatistics = false;

	// TODO: Implement reading/writing
	/// <summary>
	/// The name of the generation results statistics file.
	/// </summary>
	//std::string statisticsFileName;

	///<summary>
	/// The number of genotypes to load into an initial population; to be set in some UI.
	/// </summary>
	int genotypesToLoad = 0;

	/// <summary>
	/// How many of the first genotypes should be saved to a file; to be set in some UI.
	/// </summary>
	int genotypesToSave = 0;

	/// <summary>
	/// The number of genotypes that are saved to a file.
	/// </summary>
	int genotypesSaved = 0;

	// The population size; to be set in some UI.
	int populationSize = 30; // (populationSize is set to a default value.)

	/// <summary>
	/// The maximum time allowed for a given evaluation of 1 population; to be set in some UI.
	/// </summary>
	float maxEvaluationTime = 15.f;

	/// <summary>
	/// The number of generations required to pass before the genetic algorithm 
	/// restarts (0 for never); to be set in some UI.
	/// </summary>
	int restartAfter = 100; // (restartAfter has a default value.)

	/// <summary>
	/// An enum describing different adaptation modes.
	/// </summary>
	enum SelectionMode { FitnessProportionate, Elitist };

	/// <summary>
	/// The adaptation mode to be used in a simulation; to be set in some UI.
	/// </summary>
	SelectionMode selectionMode;

	/// <summary>
	/// Whether this simulation should use asexual recombination; to be set in some UI.
	/// </summary>
	bool asexualRecombinationMode = false;

	/// <summary>
	/// A power used in the Fitness-Proportionate adaptation mode to select more fit genotypes over others. 
	/// Higher adaptation powers lead to more elitist populations; to be set in some UI.
	/// (Don't set adaptationPower to a value below 0, or the population will degenerate!)
	/// </summary>
	float fitnessProportionateAdaptationPower = 3.f;

	/// <summary>
	/// The topology of an agent's Feedforward Neural Network (FNN); to be set in some UI.
	/// </summary>
	std::vector<int> fnnTopology;

	/// <summary>
	/// The current population of agents.
	/// </summary>
	std::vector<Agent> agents;

public:
	// TODO: Change agentsDiedCount to a relevant variable.
	/// <summary>
	/// The number of agents in the current generation that have died.
	/// </summary>
	int agentsDiedCount;

	/// <summary>
	/// An event for when all agents have died.
	/// </summary>
	//public event System.Action AllAgentsDied;
	void AllAgentsDied ();

private:
	// The GeneticAlgorithm being used with this GeneticsManager.
	GeneticAlgorithm geneticAlgorithm;

public:
	/// <summary>
	/// The number of generations that have already passed.
	/// </summary>
	int GetGenerationCount () {
		return geneticAlgorithm.generationCount;
	}
#pragma endregion

#pragma region Constructors
public:
	void Awake();

	~GeneticsManager();
#pragma endregion

#pragma region Methods
#pragma region General
public:
	/// <summary>
	/// Starts the adaptation process.
	/// </summary>
	void StartAdaptation();

	/// <summary>
	/// Sets up an evaluation of the current population by creating new agents from the current
	/// population and then starting a new evaluation with the GameStateManager's Singleton instance.
	/// </summary>
	/// <param name="currentPopulation">The current population.</param>
	void SetUpPopulationEvaluation(std::vector<Genotype> currentPopulation);

#pragma region Helper Methods
	// TODO: Reading/writing for NNs.
	/*
	/// <summary>
	/// Writes the starting line of a statistics file, stating all a genetic algorithm's parameters.
	/// </summary>
	private void WriteStatisticsFileStart() {
		// (Environment.NewLine is the newline string for a given environment and platform.)
		File.WriteAllText(statisticsFileName + ".txt", "Evaluation of a Population with size " + populationSize +
			"using the following GA operators: " + Environment.NewLine +
			"Selection: " + geneticAlgorithm.Selection.Method.Name + Environment.NewLine +
			"Recombination: " + geneticAlgorithm.Recombination.Method.Name + Environment.NewLine +
			"Mutation: " + geneticAlgorithm.Mutation.Method.Name + Environment.NewLine +
			"FitnessCalculation: " + geneticAlgorithm.FitnessCalculationMethod.Method.Name + Environment.NewLine + Environment.NewLine);
	}

	/// <summary>
	/// Appends the current generation count and the
	/// evaluation of the best genotype to the statistics file.
	/// </summary>
	/// <param name="currentPopulation">Current population.</param>
	private void WriteStatisticsToFile(IEnumerable<Genotype> currentPopulation) {
		foreach(Genotype genotype in currentPopulation) {
			File.AppendAllText(statisticsFileName + ".txt", geneticAlgorithm.generationCount + "\t" + genotype.evaluation + Environment.NewLine);
			break; // Only write data about the first genotype.
		}
	}

	/// <summary>
	/// Saves the first saveFirstNGenotypes genotypes in currentPopulation to their own files.
	/// </summary>
	/// <param name="currentPopulation">The current population.</param>
	private void SaveGenotypes(List<Genotype> currentPopulation) {
		// Sort currentPopulation to prevent saving bad genotypes!
		currentPopulation.Sort();

		string saveFolder = statisticsFileName + "/";

		// Create a save folder if there isn't one already.
		if (!Directory.Exists(saveFolder)) {
			Directory.CreateDirectory(saveFolder);
		}

		// Create files for the first saveFirstNGenotypes genotypes.
		for (int i = 0; i < genotypesToSave; i++) {
			currentPopulation[i].SaveToFile(saveFolder + "Genotype " + ++genotypesSaved + ".txt");
		}
	}

	/// <summary>
	/// Loads the first genotypesToLoad genotypes into the first indices of the given population.
	/// </summary>
	/// <param name="currentPopulation">The current population.</param>
	private void LoadGenotypesIntoPopulation(List<Genotype> currentPopulation) {
		string saveFolder = statisticsFileName + "/";

		// Don't try to load genotypes if no genotypes have been saved in the save folder.
		if (!Directory.Exists(saveFolder)) {
			return;
		}

		// Assume that currentPopulation has already been initialized: just replace the first genotypesToLoad in currentPopulation w/ loaded genotypes.
		for (int i = 1; i <= genotypesToLoad; i++) {
			currentPopulation[i - 1] = Genotype.LoadFromFile(saveFolder + "Genotype " + i + ".txt");
		}
	}*/

	/// <summary>
	/// Checks whether the termination criterion of generation count was met.
	/// </summary>
	/// <param name="currentPopulation">The current population.</param>
	bool CheckGenerationTermination(std::vector<Genotype> currentPopulation);

	/// <summary>
	/// Called when a given genetic algorithm has been terminated.
	/// </summary>
	/// <param name="ga">A genetic algorithm.</param>
	void OnGATermination(GeneticAlgorithm ga);

private:
	/// <summary>
	/// Restarts the genetic algorithm Singleton after a given wait time.
	/// </summary>
	/// <param name="waitTime">The wait time in seconds.</param>
	void RestartAlgorithm(float waitTime);

	/// <summary>
	/// Callback for when an agent has died.
	/// </summary>
	/// <param name="agent">A given agent.</param>
	void OnAgentDied(Agent agent);
#pragma endregion
#pragma endregion

#pragma region GA Operators
	/// <summary>
	/// A selection operator for a genetic algorithm that selects fitter genotypes more often than less-fit genotypes.
	/// </summary>
	/// <param name="currentPopulation">A sorted population of evaluated genotypes.</param>
	std::vector<Genotype> FitnessProportionateSelection(std::vector<Genotype> currentPopulation);

	/*
	/// <summary>
	/// A selection operator for a genetic algorithm, using a method called "remainder stochastic sampling".
	/// </summary>
	/// <param name="currentPopulation">A sorted population of evaluated genotypes.</param>
	std::vector<Genotype> RemainderStochasticSampling(std::vector<Genotype> currentPopulation) {
		std::vector<Genotype> intermediatePopulation; intermediatePopulation.reserve(currentPopulation.size());
		unsigned int intermediatePopulationIndex = 0;

		// Save the best 2 genotypes.
		intermediatePopulation[intermediatePopulationIndex++] = currentPopulation[0];
		intermediatePopulation[intermediatePopulationIndex++] = currentPopulation[1];

		// Put an integer portion of genotypes into intermediatePopulation.
		// (This process assumes that currentPopulation is already sorted).
		for (unsigned int i = 0; i < currentPopulation.size(); i++) { // Genotype genotype in currentPopulation) {
			Genotype currentGenotype = currentPopulation[i];
			// Don't accept genotypes w/ average or below-average fitness.
			if (currentGenotype.fitness <= 0) { // (This 0 should be 1 when using the default fitness operator.)
				break;
			}
			else {
				// Select more fit genotypes more.
				for (int i = 0; i <= (int)currentGenotype.fitness; i++) { // (This '<=' should be a '<' when using the default fitness operator.)
					intermediatePopulation[intermediatePopulationIndex++] = Genotype(currentPopulation[i].GetParameterCopy());
				}
			}
		}

		// Put random genotypes into intermediatePopulation.
		for (unsigned int i = 0; i < currentPopulation.size(); i++) {//foreach(Genotype genotype in currentPopulation) {
			Genotype currentGenotype = currentPopulation[i];
			float remainder = currentGenotype.fitness - (int)currentGenotype.fitness;
			if (MathHelper.RandomRange(0.f, 1.f) < std::abs(remainder)) {
				intermediatePopulation.Add(new Genotype(genotype.GetParameterCopy()));
			}
		}

		return intermediatePopulation;
	}*/

	/// <summary>
	/// A recombination operator for a genetic algorithm; recombines random genotypes of a given intermediate population.
	/// </summary>
	/// <returns>A new, un-mutated population.</returns>
	/// <param name="intermediatePopulation">The intermediate population.</param>
	/// <param name="newPopulationSize">The size of the new population.</param>
	std::vector<Genotype> RandomRecombination(std::vector<Genotype> intermediatePopulation, int newPopulationSize);

	/// <summary>
	/// A recombination operator for a genetic algorithm; asexually selects random genotypes of a given population.
	/// </summary>
	/// <returns>A new, un-mutated population.</returns>
	/// <param name="intermediatePopulation">The intermediate population.</param>
	/// <param name="newPopulationSize">The size of the new population.</param>
	std::vector<Genotype> AsexualRecombination(std::vector<Genotype> intermediatePopulation, unsigned int newPopulationSize);

	/// <summary>
	/// Mutates all members of a new population with the default probability, while leaving the first to genotypes in the list unchanged.
	/// </summary>
	/// <param name="newPopulation">The new population.</param>
	void MutateAllButBestTwo(std::vector<Genotype> newPopulation);

	/// <summary>
	/// Mutates all the members of a new population with parameters.
	/// </summary>
	/// <param name="newPopulation">The new population.</param>
	void MutateAll(std::vector<Genotype> newPopulation);

	/// <summary>
	/// Calculates the fitness of each genotype in a population, measured as a genotype's z-score.
	/// </summary>
	/// <param name="population">A given population of genotypes.</param>
	void StandardDeviationFitnessCalculation(std::vector<Genotype> population);
#pragma endregion

#pragma region Get Methods
public:
	int GetPopulationSize() {
		return populationSize;
	}
#pragma endregion
#pragma endregion
};

