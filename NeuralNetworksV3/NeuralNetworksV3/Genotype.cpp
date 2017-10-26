#include "stdafx.h"
#include "Genotype.h"

#pragma region Constructors
Genotype::Genotype(std::vector<float> _parameters) {
	for (int i = 0; i < ((int) _parameters.size()); i++) {
		parameters[i] = _parameters[i];
	}
	fitness = 0;
	//genotypeIndex = currentGenotypeIndex++;
}

Genotype::~Genotype()
{
}
#pragma endregion

#pragma region Methods
#pragma region Get/Set
int Genotype::GetParameterCount() {
	return ((int) parameters.size());
}

float Genotype::GetParameter(int index) {
	return parameters[index];
}

void Genotype::SetParameter(int index, float value) {
	parameters[index] = value;
}
#pragma endregion

void Genotype::SetRandomParameters(float minValue, float maxValue) {
	// Check arguments.
	if (minValue > maxValue) {
		throw std::invalid_argument("The minimum value may not exceed the maximum value.");
	}

	float normalizedRand; // A normalized, random float (b/w 0 and 1).
	float range = maxValue - minValue; // The range b/w minValue and maxValue.

									   // Generate a random parameter vector by looping through each parameter,
									   // giving them random values b/w minValue and maxValue.
	for (int i = 0; i < ((int) parameters.size()); i++) {
		normalizedRand = ((float)rand()) / (float(RAND_MAX));
		parameters[i] = minValue + normalizedRand * range;
	}
}

std::vector<float> Genotype::GetParameterCopy() {
	std::vector<float> copy; copy.reserve(parameterCount);
	for (int i = 0; i < parameterCount; i++) {
		copy[i] = parameters[i];
	}

	return copy;
}

#pragma region Static Methods
Genotype Genotype::GenerateRandom(int parameterCount, float minValue, float maxValue) {
	std::vector<float> parameters; parameters.reserve(parameterCount);

	Genotype randomGenotype = Genotype(parameters);
	randomGenotype.SetRandomParameters(minValue, maxValue);

	//randomGenotype.genotypeIndex = currentGenotypeIndex++;

	return randomGenotype;
}
#pragma endregion
#pragma endregion