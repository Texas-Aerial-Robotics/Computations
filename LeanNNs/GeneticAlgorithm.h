//
// Created by peter on 2/10/18.
//

#ifndef LEANNNS_GENETICALGORITHM_H
#define LEANNNS_GENETICALGORITHM_H

#include <vector>
#include "AIAgent.h"

class GeneticAlgorithm {
public:
    // Keeps good NNs, and gets rid of bad NNs.
    static void AdaptPopulation(std::vector<AIAgent>& population);

private:
    // Sorts AI Agents in score-descending order.
    static void SortAgents (std::vector<AIAgent>& population);
};


#endif //LEANNNS_GENETICALGORITHM_H
