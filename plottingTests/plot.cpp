#include "matplotlibcpp.h"
#include <cmath>

std::vector<double> x, y;

namespace plt = matplotlibcpp;
int main() {
	x.push_back(1); // Add value 1 to first position in x array of values
	y.push_back(3); // Add value 3 to first position in x array of values
	plt::plot(x, y, "r-"); // Plot "x, y" as "red and dashed"
	plt::show(); // Show in the window
	x.push_back(2);
	y.push_back(4);
	plt::plot(x, y, "r-");
	plt::show();
	x.push_back(3);
	y.push_back(2);
	plt::plot(x, y, "r-");
	plt::show();
	x.push_back(2);
	y.push_back(2.5);
	plt::plot(x, y, "r-");
	plt::show();
}
