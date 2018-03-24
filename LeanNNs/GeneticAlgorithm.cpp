//
// Created by peter on 2/10/18.
//

#include "GeneticAlgorithm.h"
#include <algorithm> // For sort.

void GeneticAlgorithm::AdaptPopulation() {
    std::sort(population.begin(), population.end(), AIAgent::cmp);
}

