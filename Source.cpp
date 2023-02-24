#include "HashTable.h"

int main() {
	std::vector<double> vec{ 10.25, -23.25, 10.250, -5.25, 0.01, 0.726, 15.6, 14.81 };
	HashTable mynewtable = HashTable(vec);
	mynewtable.hash(vec);
	mynewtable.print();
	mynewtable.searchelem(0.93);
	mynewtable.searchelem(1.93);
	mynewtable.searchelem(0.4);
	mynewtable.searchelem(10.93);
	double l = 1.0;
	
	while (l != 0) {
		std::cout << "Enter number: ";
		std::cin >> l;
		mynewtable.searchelem(l);
	}
}