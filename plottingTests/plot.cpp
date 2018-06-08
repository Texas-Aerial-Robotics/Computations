#include "matplotlibcpp.h"
#include <cmath>

std::vector<double> x, y;

namespace plt = matplotlibcpp;
int main() {
	x.push_back(1); // Add value 1 to first position in x array of values
	y.push_back(3); // Add value 3 to first position in x array of values
	plt::ion(); // Make interactive
	plt::ylim(-10,10); // Set y limits
	plt::xlim(-10,10); // Set x limits
	plt::plot(x, y, "ro"); // Plot "x, y" as "red and dashed"
	plt::pause(1); // Just needs to be larger than 0.0001
	x.push_back(2);
	y.push_back(4);
	plt::plot(x, y, "ro");
	plt::pause(1);
	plt::draw();
	x.push_back(3);
	y.push_back(2);
	plt::plot(x, y, "ro");
	plt::pause(1);
	plt::draw();
	x.push_back(2);
	y.push_back(2.5);
	plt::plot(x, y, "ro");
	plt::pause(1);
	plt::draw();
}
