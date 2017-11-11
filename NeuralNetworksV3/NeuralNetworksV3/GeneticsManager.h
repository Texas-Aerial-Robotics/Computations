#pragma once

/// <summary>
/// Singleton class for managing the adaptation process.
/// </summary>
class GeneticsManager : MonoBehaviour {
public:
	GeneticsManager();
	~GeneticsManager();

	#pragma region Members
		/// <summary>
		/// The one and only GeneticsManager instance.
		/// </summary>
		public static GeneticsManager instance{
		get;
	private set;
	}

		// Whether or not the results of each generation shall be written to a file; to be set in the Unity Editor.
		[SerializeField]
	private bool saveStatistics = false;

	/// <summary>
	/// The name of the generation results statistics file.
	/// </summary>
	private string statisticsFileName;

	///<summary>
	/// The number of genotypes to load into an initial population; to be set in the Unity Editor.
	/// </summary>
	[SerializeField]
	private int genotypesToLoad = 0;

	/// <summary>
	/// How many of the first genotypes should be saved to a file; to be set in the Unity Editor.
	/// </summary>
	[SerializeField]
	private int genotypesToSave = 0;

	/// <summary>
	/// The number of genotypes that are saved to a file.
	/// </summary>
	private int genotypesSaved = 0;

	// The population size; to be set in the Unity Editor.
	[SerializeField]
	private int populationSize = 30; // (populationSize is set to a default value.)

									 /// <summary>
									 /// The maximum time allowed for a given evaluation of 1 population; to be set in the Unity Editor.
									 /// </summary>
	[SerializeField]
	private float maxEvaluationTime = 15f;

	/// <summary>
	/// The number of generations required to pass before the genetic algorithm 
	/// restarts (0 for never); to be set in the Unity Editor.
	/// </summary>
	[SerializeField]
	private int restartAfter = 100; // (restartAfter has a default value.)

									/// <summary>
									/// An enum describing different adaptation modes.
									/// </summary>
	private enum SelectionMode { FitnessProportionate, Elitist, RemainderStochastic };

	/// <summary>
	/// The adaptation mode to be used in a simulation; to be set in the Unity Editor.
	/// </summary>
	[SerializeField]
	private SelectionMode selectionMode;

	/// <summary>
	/// Whether this simulation should use asexual recombination; to be set in the Unity Editor.
	/// </summary>
	[SerializeField]
	private bool asexualRecombinationMode = false;

	/// <summary>
	/// A power used in the Fitness-Proportionate adaptation mode to select more fit genotypes over others. 
	/// Higher adaptation powers lead to more elitist populations; to be set in the Unity editor.
	/// (Don't set adaptationPower to a value below 0, or the population will degenerate!)
	/// </summary>
	[SerializeField]
	private float fitnessProportionateAdaptationPower = 3f;

	/// <summary>
	/// The topology of an agent's Feedforward Neural Network (FNN); to be set in the Unity Editor.
	/// </summary>
	[SerializeField]
	private int[] fnnTopology;

	/// <summary>
	/// The current population of agents.
	/// </summary>
	private List<Agent> agents = new List<Agent>();

	/// <summary>
	/// The number of agents in the current generation that have died.
	/// </summary>
	public int agentsDiedCount{ get; private set; }

		/// <summary>
		/// An event for when all agents have died.
		/// </summary>
	public event System.Action AllAgentsDied;

	// The GeneticAlgorithm being used with this GeneticsManager.
	private GeneticAlgorithm geneticAlgorithm;

	/// <summary>
	/// The number of generations that have already passed.
	/// </summary>
	public int generationCount{
		get{ return geneticAlgorithm.generationCount; }
	}
		#pragma endregion

		#region Constructors
		void Awake() {
		// If instance (a static variable in the GeneticsManager class) is already set,
		// then there must be another GeneticsManager in the scene, which is bad b/c GeneticsManager
		// has a Singleton design.
		if (instance != null) {
			Debug.LogError("There is more than one GeneticsManager in the Scene.");
			return;
		}
		instance = this;
	}
	#endregion

		#region Methods
		/// <summary>
		/// Starts the adaptation process.
		/// </summary>
		public void StartAdaptation() {
		// Create a neural network to get a parameter count.
		NeuralNetwork nn = new NeuralNetwork(fnnTopology);

		// Set up the Genetic Algorithm.
		geneticAlgorithm = new GeneticAlgorithm(nn.weightCount, populationSize);
		genotypesSaved = 0;

		geneticAlgorithm.Evaluation = SetUpPopulationEvaluation;

		// Change the recombination mode of the simulation based on whether asexualRecombination is true.
		if (asexualRecombinationMode) {
			geneticAlgorithm.Recombination = AsexualRecombination;
		}
		else {
			geneticAlgorithm.Recombination = RandomRecombination;
		}

		// MutateAllButBestTwo is the only viable genetic mutation operator for now.
		geneticAlgorithm.Mutation = MutateAllButBestTwo;

		// Change the selection mode of the simulation based on a given SelectionMode.
		switch (selectionMode) {
		case SelectionMode.FitnessProportionate:
			geneticAlgorithm.Selection = FitnessProportionateSelection;
			geneticAlgorithm.FitnessCalculationMethod = StandardDeviationFitnessCalculation;
			break;
		case SelectionMode.Elitist:
			geneticAlgorithm.Selection = GeneticAlgorithm.DefaultSelectionOperator;
			geneticAlgorithm.FitnessCalculationMethod = StandardDeviationFitnessCalculation;

			// Elitist recombination uses the default recombination operator instead of RandomRecombination.
			if (!asexualRecombinationMode) {
				geneticAlgorithm.Recombination = GeneticAlgorithm.DefaultRecombinationOperator;
			}
			break;
		case SelectionMode.RemainderStochastic:
			geneticAlgorithm.Selection = RemainderStochasticSampling;
			geneticAlgorithm.FitnessCalculationMethod = StandardDeviationFitnessCalculation;
			break;
		}

		// Subscribe the genetic algorithm's EvaluationFinished() method to the AllAgentsDied event.
		// (So EvaluationFinished() gets called when the AllAgentsDied event is fired.)
		AllAgentsDied += geneticAlgorithm.EvaluationFinished;

		// Statistics! (And Saving/Loading genotypes.)
		if (saveStatistics) {
			statisticsFileName = "Last Simulation Statistics";//"Evaluation - " + DateTime.Now.ToString ("yyyy_MM_dd_HH-mm-ss");
			WriteStatisticsFileStart();
			// Subscribe the WriteStatisticsToFile() method to geneticAlgorithm's FitnessCalculationFinished event.
			geneticAlgorithm.FitnessCalculationFinished += WriteStatisticsToFile;

			// Loading/saving genotypes.
			geneticAlgorithm.GenotypeLoadingMethod += LoadGenotypesIntoPopulation;
			geneticAlgorithm.GenotypeSavingMethod += SaveGenotypes;
		}

		// Restart logic
		if (restartAfter > 0) {
			geneticAlgorithm.TerminationCriteria += CheckGenerationTermination;
			geneticAlgorithm.AlgorithmTerminated += OnGATermination;
		}

		// Set the maximum allowed evaluation time for Helicopters.
		Helicopter.SetMaxEvaluationTime(maxEvaluationTime);

		geneticAlgorithm.Start();
	}

	#region Helper Methods
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
	}

	/// <summary>
	/// Checks whether the termination criterion of generation count was met.
	/// </summary>
	/// <param name="currentPopulation">The current population.</param>
	private bool CheckGenerationTermination(IEnumerable<Genotype> currentPopulation) {
		return geneticAlgorithm.generationCount >= restartAfter;
	}

	/// <summary>
	/// Called when a given genetic algorithm has been terminated.
	/// </summary>
	/// <param name="ga">A genetic algorithm.</param>
	private void OnGATermination(GeneticAlgorithm ga) {
		// Unsubscribe the EvaluationFinished() method from the AllAgentsDied event.
		AllAgentsDied -= ga.EvaluationFinished;

		RestartAlgorithm(5.0f);
	}

	/// <summary>
	/// Restarts the genetic algorithm Singleton after a given wait time.
	/// </summary>
	/// <param name="waitTime">The wait time in seconds.</param>
	private void RestartAlgorithm(float waitTime) {
		Invoke("StartAdaptation", waitTime);
	}

	/// <summary>
	/// Sets up an evaluation of the current population by creating new agents from the current
	/// population and then starting a new evaluation with the GameStateManager's Singleton instance.
	/// </summary>
	/// <param name="currentPopulation">The current population.</param>
	private void SetUpPopulationEvaluation(IEnumerable<Genotype> currentPopulation) {
		// Create new agents from currentPopulation.
		agents.Clear();
		agentsDiedCount = 0;

		foreach(Genotype genotype in currentPopulation) {
			agents.Add(new Agent(genotype, MathHelper.SoftSignFunction, fnnTopology));
		}

		for (int i = 0; i < agents.Count; i++) {
			agents[i].AgentDied += OnAgentDied;
		}

		GameStateManager.instance.QueueForEvaluation(agents);
	}

	/// <summary>
	/// Callback for when an agent has died.
	/// </summary>
	/// <param name="agent">A given agent.</param>
	private void OnAgentDied(Agent agent) {
		agentsDiedCount++;

		// Call AllAgentsDied if all agents have died, and AllAgentsDied points to a method.
		if (agentsDiedCount == populationSize && AllAgentsDied != null) {
			AllAgentsDied();
		}
	}
	#endregion

		#region GA Operators
		/// <summary>
		/// A selection operator for a genetic algorithm that selects fitter genotypes more often than less-fit genotypes.
		/// </summary>
		/// <param name="currentPopulation">A sorted population of evaluated genotypes.</param>
		private List<Genotype> FitnessProportionateSelection(List<Genotype> currentPopulation) {
		List<Genotype> intermediatePopulation = new List<Genotype>();

		// Save the best 2 genotypes.
		intermediatePopulation.Add(currentPopulation[0]);
		intermediatePopulation.Add(currentPopulation[1]);

		// Get the min and max fitnesses in the population.
		// (Assume that currentPopulation is sorted in fitness-descending order.)
		float minFitness = currentPopulation[currentPopulation.Count - 1].fitness;
		float maxFitness = currentPopulation[0].fitness;

		// Select genotypes based on their fitnesses.
		float selectionChance;
		foreach(Genotype genotype in currentPopulation) {
			selectionChance = Mathf.Pow(Mathf.InverseLerp(minFitness, maxFitness, genotype.fitness), fitnessProportionateAdaptationPower); // Raise fitnesses to a power to give mediocre genotypes to make selection more/less elitist.
			if (UnityEngine.Random.Range(0f, 1f) <= selectionChance)
				intermediatePopulation.Add(genotype);
		}

		return intermediatePopulation;
	}

	/// <summary>
	/// A selection operator for a genetic algorithm, using a method called "remainder stochastic sampling".
	/// </summary>
	/// <param name="currentPopulation">A sorted population of evaluated genotypes.</param>
	private List<Genotype> RemainderStochasticSampling(List<Genotype> currentPopulation) {
		List<Genotype> intermediatePopulation = new List<Genotype>();

		// Save the best 2 genotypes.
		intermediatePopulation.Add(currentPopulation[0]);
		intermediatePopulation.Add(currentPopulation[1]);

		// Put an integer portion of genotypes into intermediatePopulation.
		// (This process assumes that currentPopulation is already sorted).
		foreach(Genotype genotype in currentPopulation) {
			// Don't accept genotypes w/ average or below-average fitness.
			if (genotype.fitness <= 0) { // (This 0 should be 1 when using the default fitness operator.)
				break;
			}
			else {
				// Select more fit genotypes more.
				for (int i = 0; i <= (int)genotype.fitness; i++) { // (This '<=' should be a '<' when using the default fitness operator.)
					intermediatePopulation.Add(new Genotype(genotype.GetParameterCopy()));
				}
			}
		}

		// Put random genotypes into intermediatePopulation.
		foreach(Genotype genotype in currentPopulation) {
			float remainder = genotype.fitness - (int)genotype.fitness;
			if (UnityEngine.Random.Range(0f, 1f) < Mathf.Abs(remainder)) {
				intermediatePopulation.Add(new Genotype(genotype.GetParameterCopy()));
			}
		}

		return intermediatePopulation;
	}

	/// <summary>
	/// A recombination operator for a genetic algorithm; recombines random genotypes of a given intermediate population.
	/// </summary>
	/// <returns>A new, un-mutated population.</returns>
	/// <param name="intermediatePopulation">The intermediate population.</param>
	/// <param name="newPopulationSize">The size of the new population.</param>
	private List<Genotype> RandomRecombination(List<Genotype> intermediatePopulation, int newPopulationSize) {
		// Check arguments.
		if (intermediatePopulation.Count < 2)
			throw new ArgumentException("The intermediate population has to be at least of size 2 for this operator");

		if (newPopulationSize < 2)
			throw new ArgumentException("The new population size must be at least 2 for this operator.");

		List<Genotype> newPopulation = new List<Genotype>();
		// Always add the best two (unmodified) genotypes to newPopulation.
		newPopulation.Add(intermediatePopulation[0]);
		newPopulation.Add(intermediatePopulation[1]);

		// Add new genotypes to the new population until there are newPopulationSize genotypes in the new population.
		while (newPopulation.Count < newPopulationSize) {
			// Get two random indices that are not the same.
			int randomIndex1 = UnityEngine.Random.Range(0, intermediatePopulation.Count);
			int randomIndex2 = UnityEngine.Random.Range(0, intermediatePopulation.Count);
			while (randomIndex1 == randomIndex2) {
				randomIndex2 = UnityEngine.Random.Range(0, intermediatePopulation.Count);
			}

			Genotype offspring1, offspring2;
			GeneticAlgorithm.CompleteCrossover(intermediatePopulation[randomIndex1], intermediatePopulation[randomIndex2],
				GeneticAlgorithm.defCrossSwapProb, out offspring1, out offspring2);

			newPopulation.Add(offspring1);
			// Add both offspring unless there's no room in newPopulation for offspring2.
			if (newPopulation.Count < newPopulationSize) {
				newPopulation.Add(offspring2);
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
	private List<Genotype> AsexualRecombination(List<Genotype> intermediatePopulation, int newPopulationSize) {
		// Check arguments.
		if (newPopulationSize < 2)
			throw new ArgumentException("The new population size must be at least 2 for this operator.");

		List<Genotype> newPopulation = new List<Genotype>();
		// Always add the best two (unmodified) genotypes to newPopulation.
		newPopulation.Add(intermediatePopulation[0]);
		newPopulation.Add(intermediatePopulation[1]);

		// Add new genotypes to the new population until there are newPopulationSize genotypes in the new population.
		while (newPopulation.Count < newPopulationSize) {
			// Get two random indices that are not the same.
			int randomIndex1 = UnityEngine.Random.Range(0, intermediatePopulation.Count);
			int randomIndex2 = UnityEngine.Random.Range(0, intermediatePopulation.Count);
			while (randomIndex1 == randomIndex2) {
				randomIndex2 = UnityEngine.Random.Range(0, intermediatePopulation.Count);
			}

			// Select 2 genotypes, and COPY them (don't just add them to the new population).
			newPopulation.Add(new Genotype(intermediatePopulation[randomIndex1].GetParameterCopy()));
			// Add both of the selected genotypes unless there's no room in newPopulation for the 2nd genotype.
			if (newPopulation.Count < newPopulationSize) {
				newPopulation.Add(new Genotype(intermediatePopulation[randomIndex2].GetParameterCopy()));
			}
		}

		return newPopulation;
	}

	/// <summary>
	/// Mutates all members of a new population with the default probability, while leaving the first to genotypes in the list unchanged.
	/// </summary>
	/// <param name="newPopulation">The new population.</param>
	private void MutateAllButBestTwo(List<Genotype> newPopulation) {
		for (int i = 2; i < newPopulation.Count; i++) {
			if (UnityEngine.Random.Range(0f, 1f) < GeneticAlgorithm.defMutationPerc) {
				GeneticAlgorithm.MutateGenotype(newPopulation[i], GeneticAlgorithm.defMutationProb, GeneticAlgorithm.defMutationAmount);
			}
		}
	}

	/// <summary>
	/// Mutates all the members of a new population with parameters.
	/// </summary>
	/// <param name="newPopulation">The new population.</param>
	private void MutateAll(List<Genotype> newPopulation) {
		foreach(Genotype genotype in newPopulation) {
			if (UnityEngine.Random.Range(0f, 1f) < GeneticAlgorithm.defMutationPerc) {
				GeneticAlgorithm.MutateGenotype(genotype, GeneticAlgorithm.defMutationProb, GeneticAlgorithm.defMutationAmount);
			}
		}
	}

	/// <summary>
	/// Calculates the fitness of each genotype in a population, measured as a genotype's z-score.
	/// </summary>
	/// <param name="population">A given population of genotypes.</param>
	private void StandardDeviationFitnessCalculation(IEnumerable<Genotype> population) {
		// Get the sample mean evaluation.
		int currentPopulationSize = 0;
		float sampleMeanEval = 0f;
		foreach(Genotype genotype in population) {
			sampleMeanEval += genotype.evaluation;

			if (genotype.evaluation == 0)
				Debug.Log("Problem!");

			currentPopulationSize++;
		}

		sampleMeanEval /= currentPopulationSize;

		// Get the standard deviation of the sample.
		float standardDev = 0;
		foreach(Genotype genotype in population) {
			standardDev += Mathf.Pow((genotype.fitness - sampleMeanEval), 2);
		}

		standardDev = Mathf.Sqrt(standardDev / (currentPopulationSize - 1));

		// Assign fitnesses (measured in standard deviations from the population mean) to the genotypes.
		// (This is a z-score!)
		foreach(Genotype genotype in population) {
			genotype.fitness = (genotype.evaluation - sampleMeanEval) / standardDev;
		}
	}
	#endregion

		#pragma region Get Methods
		public int GetPopulationSize() {
		return populationSize;
	}
	#pragma endregion
	#endregion
};

