#include "stdafx.h"
#include "GeneticsManager.h"

#pragma region Constructors
void GeneticsManager::Awake() {
	// If instance (a static variable in the GeneticsManager class) is already set,
	// then there must be another GeneticsManager in the scene, which is bad b/c GeneticsManager
	// has a Singleton design.
	if (GeneticsManager::instanceCreated) {
		throw std::invalid_argument("There is already a GeneticsManager!");
		return;
	}
	else {
		instance = *this;
	}
}
#pragma endregion

#pragma region Methods
#pragma region General
/// <summary>
/// Starts the adaptation process.
/// </summary>
void GeneticsManager::StartAdaptation() {
	// Create a neural network to get a parameter count.
	NeuralNetwork nn = NeuralNetwork(fnnTopology);

	// Set up the Genetic Algorithm.
	geneticAlgorithm = GeneticAlgorithm(nn.weightCount, populationSize);
	genotypesSaved = 0;

	geneticAlgorithm.Evaluation = SetUpPopulationEvaluation;

	// Change the recombination mode of the simulation based on whether asexualRecombination is true.
	if (asexualRecombinationMode) {
		geneticAlgorithm.RecombinationOperator = &AsexualRecombination;
	}
	else {
		geneticAlgorithm.RecombinationOperator = RandomRecombination;
	}

	// MutateAllButBestTwo is the only viable genetic mutation operator for now.
	geneticAlgorithm.MutationOperator = MutateAllButBestTwo;

	// Change the selection mode of the simulation based on a given SelectionMode.
	/*switch (selectionMode) {
	case SelectionMode::FitnessProportionate:
		geneticAlgorithm.SelectionOperator = FitnessProportionateSelection;
		geneticAlgorithm.FitnessCalculationMethod = StandardDeviationFitnessCalculation;
		break;
	case SelectionMode::Elitist:
		geneticAlgorithm.SelectionOperator = GeneticAlgorithm::DefaultSelectionOperator;
		geneticAlgorithm.FitnessCalculationMethod = StandardDeviationFitnessCalculation;

		// Elitist recombination uses the default recombination operator instead of RandomRecombination.
		if (!asexualRecombinationMode) {
			geneticAlgorithm.RecombinationOperator = GeneticAlgorithm::DefaultRecombinationOperator;
		}
		break;
	}*/

	// Subscribe the genetic algorithm's EvaluationFinished() method to the AllAgentsDied event.
	// (So EvaluationFinished() gets called when the AllAgentsDied event is fired.)
	
	//AllAgentsDied += geneticAlgorithm.EvaluationFinished;

	// TODO: Statistics! (And Saving/Loading genotypes.)
	/*if (saveStatistics) {
	statisticsFileName = "Last Simulation Statistics";//"Evaluation - " + DateTime.Now.ToString ("yyyy_MM_dd_HH-mm-ss");
	WriteStatisticsFileStart();
	// Subscribe the WriteStatisticsToFile() method to geneticAlgorithm's FitnessCalculationFinished event.
	geneticAlgorithm.FitnessCalculationFinished += WriteStatisticsToFile;

	// Loading/saving genotypes.
	geneticAlgorithm.GenotypeLoadingMethod += LoadGenotypesIntoPopulation;
	geneticAlgorithm.GenotypeSavingMethod += SaveGenotypes;
	}*/

	// Restart logic
	if (restartAfter > 0) {
		geneticAlgorithm.CheckTerminationCriteria = CheckGenerationTermination;
		geneticAlgorithm.AlgorithmTerminated = OnGATermination;
	}

	// TODO: Make a relevant class to link Gazebo simulations w/ NNs.
	// Set the maximum allowed evaluation time for Helicopters.
	//Helicopter.SetMaxEvaluationTime(maxEvaluationTime);

	geneticAlgorithm.Start();
}

void GeneticsManager::AllAgentsDied() {
	geneticAlgorithm.EvaluationFinished();
}

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
bool GeneticsManager::CheckGenerationTermination(std::vector<Genotype> currentPopulation) {
	return geneticAlgorithm.generationCount >= restartAfter;
}

/// <summary>
/// Called when a given genetic algorithm has been terminated.
/// </summary>
/// <param name="ga">A genetic algorithm.</param>
void GeneticsManager::OnGATermination(GeneticAlgorithm ga) {
	// Unsubscribe the EvaluationFinished() method from the AllAgentsDied event.
	//AllAgentsDied -= ga.EvaluationFinished;

	RestartAlgorithm(5.0f);
}

/// <summary>
/// Restarts the genetic algorithm Singleton after a given wait time.
/// </summary>
/// <param name="waitTime">The wait time in seconds.</param>
void GeneticsManager::RestartAlgorithm(float waitTime) {
	Invoke("StartAdaptation", waitTime);
}

/// <summary>
/// Sets up an evaluation of the current population by creating new agents from the current
/// population and then starting a new evaluation with the GameStateManager's Singleton instance.
/// </summary>
/// <param name="currentPopulation">The current population.</param>
void GeneticsManager::SetUpPopulationEvaluation(std::vector<Genotype> currentPopulation) {
	// Create new agents from currentPopulation.
	agents.Clear();
	agentsDiedCount = 0;

	for (unsigned int i = 0; i < currentPopulation.size(); i++) {//foreach(Genotype genotype in currentPopulation) {
																	//agents.Add(new Agent(genotype, MathHelper.SoftSignFunction, fnnTopology));
		agents[i] = Agent(genotype, MathHelper::SoftSignFunction, fnnTopology);
	}

	for (unsigned int i = 0; i < agents.size(); i++) {
		agents[i].AgentDied = OnAgentDied;
	}

	GameStateManager::instance.QueueForEvaluation(agents);
}

/// <summary>
/// Callback for when an agent has died.
/// </summary>
/// <param name="agent">A given agent.</param>
void GeneticsManager::OnAgentDied(Agent agent) {
	agentsDiedCount++;

	// Call AllAgentsDied if all agents have died, and AllAgentsDied points to a method.
	if (agentsDiedCount == populationSize && AllAgentsDied != NULL) {
		AllAgentsDied();
	}
}
#pragma endregion
#pragma endregion

#pragma region GA Operators
/// <summary>
/// A selection operator for a genetic algorithm that selects fitter genotypes more often than less-fit genotypes.
/// </summary>
/// <param name="currentPopulation">A sorted population of evaluated genotypes.</param>
std::vector<Genotype> GeneticsManager::FitnessProportionateSelection(std::vector<Genotype> currentPopulation) {
	std::vector<Genotype> intermediatePopulation; intermediatePopulation.reserve(currentPopulation.size());

	// Current index in intermediatePopulation
	unsigned int intermediatePopulationIndex = 0;

	// Save the best 2 genotypes.
	intermediatePopulation[intermediatePopulationIndex++] = currentPopulation[0];
	intermediatePopulation[intermediatePopulationIndex++] = currentPopulation[1];

	// Get the min and max fitnesses in the population.
	// (Assume that currentPopulation is sorted in fitness-descending order.)
	float minFitness = currentPopulation[currentPopulation.size() - 1].fitness;
	float maxFitness = currentPopulation[0].fitness;

	// Select genotypes based on their fitnesses.
	float selectionChance;
	for (unsigned int i = 0; i < currentPopulation.size(); i++) { //foreach(Genotype genotype in currentPopulation) {
		selectionChance = std::pow(MathHelper::InverseLerp(minFitness, maxFitness, currentPopulation[i].fitness), fitnessProportionateAdaptationPower); // Raise fitnesses to a power to give mediocre genotypes to make selection more/less elitist.
		if (MathHelper::RandomRange(0.f, 1.f) <= selectionChance)
			intermediatePopulation[intermediatePopulationIndex++] = currentPopulation[i];
	}

	return intermediatePopulation;
}

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
std::vector<Genotype> GeneticsManager::RandomRecombination(std::vector<Genotype> intermediatePopulation, int newPopulationSize) {
	// Check arguments.
	if (intermediatePopulation.size() < 2)
		throw std::invalid_argument("The intermediate population has to be at least of size 2 for this operator");

	if (newPopulationSize < 2)
		throw std::invalid_argument("The new population size must be at least 2 for this operator.");

	// Current index of the new population
	unsigned int newPopIndex = 0;

	std::vector<Genotype> newPopulation; newPopulation.reserve(newPopulationSize);
	// Always add the best two (unmodified) genotypes to newPopulation.
	newPopulation[newPopIndex++] = intermediatePopulation[0];
	newPopulation[newPopIndex++] = intermediatePopulation[1];

	// Add new genotypes to the new population until there are newPopulationSize genotypes in the new population.
	while (newPopulation.size() < newPopulationSize) {
		// Get two random indices that are not the same.
		int randomIndex1 = (int)MathHelper::RandomRange(0.f, (float)intermediatePopulation.size());
		int randomIndex2 = (int)MathHelper::RandomRange(0.f, (float)intermediatePopulation.size());
		while (randomIndex1 == randomIndex2) {
			randomIndex2 = (int)MathHelper::RandomRange(0.f, (float)intermediatePopulation.size());
		}

		Genotype offspring1, offspring2;
		GeneticAlgorithm::CompleteCrossover(intermediatePopulation[randomIndex1], intermediatePopulation[randomIndex2],
			GeneticAlgorithm::defCrossSwapProb, offspring1, offspring2);

		newPopulation[newPopIndex++] = offspring1;
		// Add both offspring unless there's no room in newPopulation for offspring2.
		if (newPopulation.size() < newPopulationSize) {
			newPopulation[newPopIndex++] = offspring2;
		}
	}

	return newPopulation;
}

/// <summary>
/// A recombination operator for a genetic algorithm; asexually selects random genotypes of a given population.
/// </summary>
/// <returns>A new, un-mutated population.</returns>
/// <param name="intermediatePopulation">The intermediate population.</param>
/// <param name="newPopulationSize">The size of the new population.</param>
std::vector<Genotype> GeneticsManager::AsexualRecombination(std::vector<Genotype> intermediatePopulation, unsigned int newPopulationSize) {
	// Check arguments.
	if (newPopulationSize < 2)
		throw std::invalid_argument("The new population size must be at least 2 for this operator.");

	// Current index of the new population
	unsigned int newPopIndex = 0;

	std::vector<Genotype> newPopulation; newPopulation.reserve(newPopulationSize);
	// Always add the best two (unmodified) genotypes to newPopulation.
	newPopulation[newPopIndex++] = intermediatePopulation[0];
	newPopulation[newPopIndex++] = intermediatePopulation[1];

	// Add new genotypes to the new population until there are newPopulationSize genotypes in the new population.
	while (newPopulation.size() < newPopulationSize) {
		// Get two random indices that are not the same.
		int randomIndex1 = MathHelper::RandomRange(0, intermediatePopulation.size());
		int randomIndex2 = MathHelper::RandomRange(0, intermediatePopulation.size());
		while (randomIndex1 == randomIndex2) {
			randomIndex2 = MathHelper::RandomRange(0, intermediatePopulation.size());
		}

		// Select 2 genotypes, and COPY them (don't just add them to the new population).
		newPopulation[newPopIndex++] = Genotype(intermediatePopulation[randomIndex1].GetParameterCopy());
		// Add both of the selected genotypes unless there's no room in newPopulation for the 2nd genotype.
		if (newPopulation.size() < newPopulationSize) {
			newPopulation[newPopIndex++] = Genotype(intermediatePopulation[randomIndex2].GetParameterCopy());
		}
	}

	return newPopulation;
}

/// <summary>
/// Mutates all members of a new population with the default probability, while leaving the first to genotypes in the list unchanged.
/// </summary>
/// <param name="newPopulation">The new population.</param>
void GeneticsManager::MutateAllButBestTwo(std::vector<Genotype> newPopulation) {
	for (int i = 2; i < newPopulation.size(); i++) {
		if (MathHelper::RandomRange(0.f, 1.f) < GeneticAlgorithm::defMutationProp) {
			GeneticAlgorithm::MutateGenotype(newPopulation[i], GeneticAlgorithm::defMutationProb, GeneticAlgorithm::defMutationAmount);
		}
	}
}

/// <summary>
/// Mutates all the members of a new population with parameters.
/// </summary>
/// <param name="newPopulation">The new population.</param>
void GeneticsManager::MutateAll(std::vector<Genotype> newPopulation) {
	for (unsigned int i = 0; i < newPopulation.size(); i++) {//foreach(Genotype genotype in newPopulation) {
		if (MathHelper::RandomRange(0.f, 1.f) < GeneticAlgorithm::defMutationProp) {
			GeneticAlgorithm::MutateGenotype(newPopulation[i], GeneticAlgorithm::defMutationProb, GeneticAlgorithm::defMutationAmount);
		}
	}
}

/// <summary>
/// Calculates the fitness of each genotype in a population, measured as a genotype's z-score.
/// </summary>
/// <param name="population">A given population of genotypes.</param>
void GeneticsManager::StandardDeviationFitnessCalculation (std::vector<Genotype> population) {
	// Get the sample mean evaluation.
	int currentPopulationSize = 0;
	float sampleMeanEval = 0.f;
	for (unsigned int i = 0; i < population.size(); i++) {
		Genotype genotype = population[i];
		sampleMeanEval += genotype.evaluation;

		// TODO: Add basic text output.
		if (genotype.evaluation == 0)
			Debug.Log("Problem!");

		currentPopulationSize++;
	}

	sampleMeanEval /= currentPopulationSize;

	// Get the standard deviation of the sample.
	float standardDev = 0;
	for (unsigned int i = 0; i < population.size(); i++) { //foreach(Genotype genotype in population) {
		Genotype genotype = population[i];
		standardDev += std::pow((genotype.fitness - sampleMeanEval), 2);
	}

	standardDev = std::sqrt(standardDev / (currentPopulationSize - 1));

	// Assign fitnesses (measured in standard deviations from the population mean) to the genotypes.
	// (This is a z-score!)
	for (unsigned int i = 0; i < population.size(); i++) { //foreach(Genotype genotype in population) {
		Genotype genotype = population[i];
		genotype.fitness = (genotype.evaluation - sampleMeanEval) / standardDev;
	}
}
#pragma endregion

#pragma region Get Methods

int GeneticsManager::GetPopulationSize() {
	return populationSize;
}
#pragma endregion
#pragma endregion