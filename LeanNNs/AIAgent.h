//
// Created by peter on 2/10/18.
//

#ifndef LEANNNS_AIAGENT_H
#define LEANNNS_AIAGENT_H


class AIAgent {

    float currentScore; // Score for current trial.
    float fitness; // Total fitness across all trials.

    // Use as a Compare to sort AIAgents in fitness-ascending order.
public:
    static bool cmp (AIAgent a, AIAgent b);
    /* Things to add:
     * Compare function
     * Current score
     * Fitness
    */
};


#endif //LEANNNS_AIAGENT_H
