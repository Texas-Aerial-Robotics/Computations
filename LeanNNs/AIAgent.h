//
// Created by peter on 2/10/18.
//

#ifndef LEANNNS_AIAGENT_H
#define LEANNNS_AIAGENT_H

#include "NeuralNetwork.h"

class AIAgent {

public:
    NeuralNetwork nn; // nn associated w/ this AIAgent.
    float currentScore; // Score for current trial.
    float fitness; // Total fitness across all trials.

    // Use as a Compare to sort AIAgents in fitness-descending order.
    static bool cmp(const AIAgent &a, const AIAgent &b);

    void Score();
};


#endif //LEANNNS_AIAGENT_H
