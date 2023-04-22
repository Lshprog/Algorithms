#include "AAtree.h"


int main() {

	AAtree<ComplexNumber>* tree = new AAtree<ComplexNumber>();
	ComplexNumber number1 = ComplexNumber(1,2);
	ComplexNumber number2 = ComplexNumber(3, 2);
	ComplexNumber number3 = ComplexNumber(2, 5);
	ComplexNumber number4 = ComplexNumber(10, 5);
	ComplexNumber number5 = ComplexNumber(-1, 2);
	ComplexNumber number6 = ComplexNumber(-33, 0);
	ComplexNumber number7 = ComplexNumber(0, 0);
	ComplexNumber number8 = ComplexNumber(11, 5);

	ComplexNumber number9 = ComplexNumber(30, 0);
	ComplexNumber number10 = ComplexNumber(35, 0);

	tree->insert(number1,tree->returnroot());
	tree->insert(number2, tree->returnroot());
	tree->insert(number3, tree->returnroot());
	tree->insert(number3, tree->returnroot());
	tree->insert(number4, tree->returnroot());
	tree->insert(number6, tree->returnroot());
	tree->insert(number5, tree->returnroot());
	tree->insert(number8, tree->returnroot());
	tree->insert(number7, tree->returnroot());

	tree->remove(number4,tree->returnroot());
	tree->remove(number2,tree->returnroot());
	tree->remove(number1, tree->returnroot());
	
	ANode<ComplexNumber>* num4 = new ANode<ComplexNumber>(number4);
	std::cout<<"Level: "<< tree->search(num4,tree->returnroot())<< std::endl;

	tree->insert(number9, tree->returnroot());
	tree->printTreeOut(tree->returnroot());
	std::cout << std::endl;
	
	tree->insert(number10, tree->returnroot());
	tree->printTreeOut(tree->returnroot());
	std::cout << std::endl;

	tree->remove(number5, tree->returnroot());
	tree->printTreeOut(tree->returnroot());


	

}