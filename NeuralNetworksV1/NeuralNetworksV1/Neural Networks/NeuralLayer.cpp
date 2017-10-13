class NeuralLayer {

	// Notes to myself:
	// "Pointer": a variable that stores the *address* of another variable
	// & - the "address-of operator"; read as "address of"

	// * - the "dereference operator"; read as "value pointed to by"

	// So the & (address-of operator) and * (dereference operator) are complementary.

	// Pointers are declared with the following syntax...
	// type * name (of the pointer)
	// (The asterisk here is NOT the dereference operator)

	// Function pointers:
	// Declared like a regular function, except the name of a function pointer is enclosed b/w parantheses, and an asterisk is inserted before the name.
	// Ex: Declaring a function pointer called "FuncPointer" that represents a function that takes a string and an int and returns a float:
	// float (*FuncPointer) (string,int)
	// ^-- (This is like "dereferencing" FuncPointer, which is the address of some function.)
	// The actual function that FuncPointer represents might be declared as "float Function (string, int)".
	//
	// Syntax for setting a function pointer's value:
	// (function_pointer_name) = &(function_name)
	// The ampersand is optional, so we can also do this to point the function pointer to the function...
	// (function_pointer_name) = (function_name)
	//
	// You also don't need to use an asterisk when calling the function associated w/ a function pointer.
	// (C++ will automatically dereference a function pointer when it's called as a function.)
	// Ex: *function_pointer_name (arguments)" is the same as "function_pointer_name (arguments)" in C++.

#pragma region Function Pointers
public:
	/// <summary>
	/// Delegate representing the activation function of an artificial neuron.
	/// </summary>
	/// <param name="input">The input value of the function.</param>
	/// <returns>The calculated output value of the function.</returns>
	float(*ActivationFunction)(float input);
#pragma endregion

#pragma region Fields
private:
	/// <summary>
	/// The number of neurons in this layer.
	/// </summary>
	int neuronCount;

	/// <summary>
	/// The number of neurons in the next layer that this layer is connected to
	/// (i.e. the number of neurons in the next layer minus the number of "bias neurons" in that layer). 
	/// </summary>
	int outputCount;

	/// <summary>
	/// The weights of the connections of this layer to the next layer.
	/// Example: weight[i][j] is the weight of the connection from the 
	/// i-th neuron of this layer to the j-th neuron of the next layer.
	/// </summary>
	public float** weights;
#pragma endregion
	
#pragma region Constructors
public:
	NeuralLayer (int neuronCount, int outputCount) {
		this.neuronCount = neuronCount;
		this.outputCount = outputCount;

		// Fully initialize the weights array.
		weights = new float**[neuronCount + 1]; // Allow for 1 bias neuron per NeuralLayer (hence neuronCount + 1).

	}
#pragma endregion

#pragma region Methods
#pragma endregion
};
