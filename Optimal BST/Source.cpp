#include "OBST.h"



int main() {

	ComplexNumber number1 = ComplexNumber(1, 2);
	ComplexNumber number2 = ComplexNumber(3, 2);
	ComplexNumber number3 = ComplexNumber(2, 5);
	ComplexNumber number4 = ComplexNumber(11, 20);

	std::vector<std::pair<ComplexNumber, int>> vec;

	vec.push_back(std::make_pair(number1, 34));
	vec.push_back(std::make_pair(number2, 8));
	vec.push_back(std::make_pair(number3, 50));
	vec.push_back(std::make_pair(number4, 20));

	OBST<ComplexNumber>* tr = new OBST<ComplexNumber>(vec);

	delete tr;

}
