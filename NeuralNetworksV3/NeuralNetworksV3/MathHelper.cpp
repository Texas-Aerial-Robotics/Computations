#include "stdafx.h"
#include "stdlib.h"; // for rand
#include "MathHelper.h"


float MathHelper::RandomRange(float minValue, float maxValue) {
	float normalizedRand; // A normalized, random float (b/w 0 and 1).
	float range = maxValue - minValue; // The range b/w minValue and maxValue.
	normalizedRand = ((float)rand()) / ((float)(RAND_MAX));
	return minValue + normalizedRand * range;
}
