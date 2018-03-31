//
// Created by peter on 2/10/18.
//

#include "GeneticAlgorithm.h"
#include "NeuralNetwork.h"
#include <algorithm> // For sort.

void GeneticAlgorithm::AdaptPopulation(std::vector<AIAgent>& population) {
    SortAgents(population);

    int badAgentStartIndex = (int) (population.size() / 2); // Bottom half.
    for (int i = badAgentStartIndex, k = 0; i < population.size(); i++, k++) {
        k %= badAgentStartIndex; // k is current good agent index.
        population[i] = population[k]; // TODO: add a NN copy constructor.
        population[i].nn.Mutate();
    }
}

void GeneticAlgorithm::SortAgents(std::vector<AIAgent>& population) {
    std::sort(population.begin(), population.end(), AIAgent::cmp);
}