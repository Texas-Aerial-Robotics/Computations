#pragma once
static class MathHelper
{
public:
	/// <summary>
	/// Returns a random value in the range b/w minValue and maxValue.
	/// </summary>
	static float RandomRange(float minValue, float maxValue);

	/// <summary>
	/// Implements the SoftSign function w/ floats. Used as a neuron activation function.
	/// </summary>
	static float SoftSignFunction(float input);

	/// <summary>
	/// Returns the interpolant parameter t that causes the interpolant value b/w a and b.
	/// </summary>
	static float InverseLerp(float a, float b, float value);
};

