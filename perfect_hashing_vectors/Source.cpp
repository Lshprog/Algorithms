#include "HashTable.h"

int main() {
	/*std::vector<std::vector<double>> vec{ {10.25, 23.1} ,{10.250, -5.25, 0.01,
		0.726, 15.6,14.81},{-5.25, -23.578,-15,-17,-5.5 ,0} };*/
	std::vector<std::vector<double>> vec
	{
	  {16.2, 10.001},
	  {129.256, -15, 450.045, 89.56, 0},
	  {-6, 2.3, 0.07, 0.08, -0.01},
	  {9752.43, -15.2, 5.3, 5.3},
	  {9752.43, -15.2, 5.3, 5.3},
	  {9752.43, 5.3,-15.2, 5.3},
	  {},
	  {10.25, 23.1, -1.326, 0.566, 14.-81.9, 18.12}
	};
	//std::vector<double> vec{ -23,-15,-17};
	HashTable mynewtable = HashTable(vec);
	bool result = mynewtable.hash(vec);
	if(result) mynewtable.print();
	mynewtable.searchelem({ 9752.43, 5.3,-15.2, 5.3 });
	mynewtable.searchelem({ 9752.43, -15.2, 5.3, 5.3 });
	mynewtable.searchelem({ 0 });

	//double l = 1.0;
	
	/*while (true) {
		
		std::cout << "\nEnter number: ";
		std::cin >> l;
		mynewtable.searchelem(l);
	}*/
}