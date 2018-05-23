#include <iostream>
#include "NeuralNetwork.h"
#include "AIAgent.h"
#include "GeneticAlgorithm.h"

int main() {
    // Test NNs:
    char* path = "/home/peter/CLionProjects/LeanNNs/NN 1";
    std::cout << "Weights: \n";
    NeuralNetwork* neuralNetwork = new NeuralNetwork({1, 3, 1});
    neuralNetwork->PrintWeights();
    printf("\n");
    NeuralNetwork::WriteToFile(*neuralNetwork, path);

    NeuralNetwork *neuralNetwork2 = NeuralNetwork::ReadFromFile(path);
    neuralNetwork2->PrintWeights();

    std::cout << "\n\nOutputs: \n";
    std::cout << "NN 1: " << neuralNetwork->FeedForward(std::vector<float> {1})[0] << "\n";
    std::cout << "NN 2: " << neuralNetwork2->FeedForward(std::vector<float> {1})[0] << "\n";


    // Test agents/GA:
    std::vector<AIAgent> population;
    population.push_back(AIAgent()); // Calls copy constructor of AIAgent class.
    population.push_back(AIAgent());
    population[0].fitness = 1;
    population[1].fitness = 2;
    GeneticAlgorithm::AdaptPopulation(population);
    for (std::vector<AIAgent>::iterator it = population.begin(); it != population.end(); it++) {

    }
    std::cout << "Hello!";

    // srand(time(NULL))
    return 0;
}