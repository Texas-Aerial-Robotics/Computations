cmake_minimum_required(VERSION 3.9)
project(LeanNNs)

set(CMAKE_CXX_STANDARD 11)

add_executable(LeanNNs main.cpp NeuralNetwork.cpp NeuralNetwork.h GeneticAlgorithm.cpp GeneticAlgorithm.h AIAgent.cpp AIAgent.h)