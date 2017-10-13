// NeuralNetworksV1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	float (*FunctionPointer)(int i) = NULL;
	if (FunctionPointer != NULL) {
		cout << "OK";
	}
	else {
		cout << "Null pointer!";
	}
	system("pause");
    return 0;
}

