//
// Created by peter on 2/10/18.
//

#include "AIAgent.h"

bool AIAgent::cmp(AIAgent a, AIAgent b) {
    return a.fitness > b.fitness;
}