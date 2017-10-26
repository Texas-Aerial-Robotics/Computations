using System;
using UnityEngine;

/// <summary>
/// Static class for math operations and constants.
/// </summary>
public static class MathHelper {
	/// <summary>
	/// The standard sigmoid function.
	/// </summary>
	/// <returns>A calculated output.</returns>
	/// <param name="input">An input value.</param>
	public static float SigmoidFunction (float input) {
		// Maximum input is 10.
		if (input > 10f)
			return 1.0f;
		// Minimum input is -10.
		else if (input < -10f)
			return 0f;
		// For the valid range of inputs, return...
		// 1 / (1 + e^(-input))
		else
			return 1 / (1 + Mathf.Exp (-input));
	}

	/// <summary>
	/// A TanH function for floats.
	/// </summary>
	/// <returns>A calculated output.</returns>
	/// <param name="input">An input value.</param>
	// (Tanh takes all real values and returns a value b/w -1 and 1.)
	public static float TanhFunction (float input) {
		if (input > 10)
			return 1f;
		else if (input < -10)
			return -1f;
		else
			return (float) Math.Tanh ((double)input);
	}

	/// <summary>
	/// A SoftSign function for floats.
	/// </summary>
	/// <returns>A calculated output.</returns>
	/// <param name="input">An input value.</param>
	// (Tanh takes all real values and returns a value b/w -1 and 1.)
	public static float SoftSignFunction (float input) {
		return input / (1 + Mathf.Abs (input));
	}
}
