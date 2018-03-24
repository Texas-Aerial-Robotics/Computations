//
// Created by peter on 2/10/18.
//

#ifndef LEANNNS_GENETICALGORITHM_H
#define LEANNNS_GENETICALGORITHM_H

#include <vector>
#include "AIAgent.h"

class GeneticAlgorithm {
    /* Things to add:
     * Vector sorting based on score
     */

    std::vector<AIAgent> population;

    // Keeps good NNs, gets rid of bad NNs.
    void AdaptPopulation();

    // Sorts AI Agents.
    void SortAgents ();
};


#endif //LEANNNS_GENETICALGORITHM_H
