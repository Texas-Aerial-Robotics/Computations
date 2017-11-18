#include "stdafx.h"
#include "stdlib.h"; // for rand
#include <complex> // for abs
#include "MathHelper.h"


float MathHelper::RandomRange(float minValue, float maxValue) {
	float normalizedRand; // A normalized, random float (b/w 0 and 1).
	float range = maxValue - minValue; // The range b/w minValue and maxValue.
	normalizedRand = ((float)rand()) / ((float)(RAND_MAX));
	return minValue + normalizedRand * range;
}

float MathHelper::SoftSignFunction(float input) {
	return input / (1.f + std::abs(input));
}

float MathHelper::InverseLerp(float a, float b, float value) {
	return (value - a) / (a - b);
}
