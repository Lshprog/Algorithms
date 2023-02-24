#include "HashTable.h"

int main() {
	std::vector<double> vec{ 10.25, 23.1, 10.250, -5.25, 0.01,
		0.726, 15.6,14.81,-5.25, -23.578,-15,-17,-5.5 ,0};
	//std::vector<double> vec{ -23,-15,-17};
	HashTable mynewtable = HashTable(vec);
	bool result = mynewtable.hash(vec);
	if(result) mynewtable.print();
	/*mynewtable.searchelem(0.93);
	mynewtable.searchelem(1.93);
	mynewtable.searchelem(0.4);
	mynewtable.searchelem(10.93)*/;
	double l = 1.0;
	
	/*while (true) {
		
		std::cout << "\nEnter number: ";
		std::cin >> l;
		mynewtable.searchelem(l);
	}*/
}