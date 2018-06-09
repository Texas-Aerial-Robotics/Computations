#include "matplotlibcpp.h"
#include <cmath>
#include <map>
#include <string>

std::vector<double> x, y;

namespace plt = matplotlibcpp;
int main() {
	x.push_back(1); // Add value 1 to first position in x array of values
	y.push_back(3); // Add value 3 to first position in x array of values
	plt::ion(); // Make interactive
	plt::ylim(-10,10); // Set y limits
	plt::xlim(-10,10); // Set x limits
	std::map<std::string, std::string> keywords;
	keywords["color"] = "red";
	keywords["marker"] = "o";
	keywords["linestyle"] = "none";
	plt::plot(x, y, keywords, 1); // Plot "x, y" as "red and dashed"
	plt::pause(1); // Just needs to be larger than 0.0001
	x.push_back(2);
	y.push_back(4);
	plt::plot(x, y, keywords, 0.8);
	plt::pause(1);
	plt::draw();
	x.push_back(3);
	y.push_back(2);
	plt::plot(x, y, keywords, 0.6);
	plt::pause(1);
	plt::draw();
	x.push_back(2);
	y.push_back(2.5);
	plt::plot(x, y, keywords, .1);
	plt::pause(1);
	plt::draw();
}
