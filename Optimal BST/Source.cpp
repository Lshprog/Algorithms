#include "OBST.h"



int main() {

	ComplexNumber number1 = ComplexNumber(1, 2);
	ComplexNumber number2 = ComplexNumber(3, 2);
	ComplexNumber number3 = ComplexNumber(2, 5);
	ComplexNumber number4 = ComplexNumber(11, 20);
	ComplexNumber number5 = ComplexNumber(50, 40);
	ComplexNumber number6 = ComplexNumber(2, 5);
	
	std::vector<std::pair<ComplexNumber, int>> vec;

	vec.push_back(std::make_pair(number1, 100));
	vec.push_back(std::make_pair(number2, 20));
	vec.push_back(std::make_pair(number3, 100));

	OBST<ComplexNumber>* tr = new OBST<ComplexNumber>(vec);

	delete tr;

}