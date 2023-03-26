#include "HashTable.h"

void remove_duplicates(std::vector<std::vector<double>>& vec)
{
	for (int i = 0; i < vec.size(); ) {
		if (vec[i].size() == 0) {
			vec.erase(vec.begin() + i);
		}
		else ++i;
	}
	sort(vec.begin(),vec.end());
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
	
}


std::pair<int, int> reduction(double number) {

	int wholepart = int(number);
	int decimalpart = int((number - wholepart) * pow(10, 4));
	return std::pair<int, int>(wholepart, decimalpart);

}


bool isPrime(int val) {
	int sq = sqrt(val);
	for (int i = 2; i <= sq; i++) {
		if (val % i == 0) {
			return false;
		}
	}
	return true;
}

int find_next_prime(int val) {
	int newv = val + 1;
	while (!isPrime(newv)) {
		newv++;
	}
	return newv;
}

HashTable::HashTable(std::vector<std::vector<double>>& vec) {
	remove_duplicates(vec);
	sizev = vec.size();
	innerhash = new std::vector<std::vector<double>>[sizev];
	coefs = new int[4 * (sizev + 1)];
	for (int i = 0; i < 4 * (sizev + 1); i++) {
		coefs[i] = 0;
	}
	srand(time(0));
}

HashTable::~HashTable() {
	delete[]innerhash;
	delete[]coefs;
}

int HashTable::hashFunctionDouble(double key,int s,size_t size)
{
	std::pair<int,int> value = reduction(key);
	int tempsize = size;
	int signindex = key > 0 ? 0 : 1;
	
	int index = ((abs(value.first) * coefs[0+s] + abs(value.second) * coefs[1+s] + signindex) % coefs[2+s]) % tempsize;

	/*std::cout << '\n';
	std::cout << coefs[0 + s] << " " << coefs[1 + s] << " " << coefs[2 + s] << " " << size << " " << value.first<<"    index: "<<index;
	std::cout << '\n';*/

	return index;
}

int HashTable::hashFunction(std::vector<double> k,int s,size_t size)
{
	int index = 0;
	int sizet = k.size();

	for (int i = 0; i < sizet; i++) {
		index += hashFunctionDouble(k[i], s, sizet)*pow(coefs[3 + s],i);
	}
	index%=coefs[2 + s];
	index%= int(size);


	return index;
}

void HashTable::print()
{
	for (int i = 0; i < sizev; i++) {
		std::cout << i << ": ";
		int temp_size = innerhash[i].size();
		for (int j = 0; j < temp_size; j++) {
			if (innerhash[i][j].size() != 0) {
				std::cout << "{";
				for (int l = 0; l < innerhash[i][j].size(); l++) {
					std::cout << innerhash[i][j][l] << ", ";
				}
				std::cout << "}";
			}
			else {
				std::cout<<" . ";
			}
		}
		std::cout << '\n';
	}

	int s = 0;
	for (int k = 0; k < 4 * (sizev + 1); k++) {
		if (k % 4 == 0) {
			std::cout << '\n';
			std::cout << "Coefs " << s << " : ";
			s++;
		}
		std::cout << coefs[k]<<" ";
		
	}
}

bool HashTable::perfect_rehash()
{
	for (int i = 0; i < sizev; i++) {
		if (innerhash[i].size() > 1) {
			bool collision_flag = false;
			int prime_change = 0;
			while (!collision_flag) {
				if (prime_change > 30) {
					std::cout << "ERROR!!! Over precision!!";
					return false;
				}
				int sizet = innerhash[i].size();
				std::vector<std::vector<double>> newvec = std::vector<std::vector<double>>(sizet* sizet);
				for(int c=0;c< sizet* sizet;c++)
				change_constants(4*(i+1), sizet, sizet +prime_change);
				collision_flag = true;
				for (int l = 0; l < sizet; l++) {
					int temp_index = hashFunction(innerhash[i][l],4*(i+1),newvec.size());
					if (newvec[temp_index].size()!=0) {
						collision_flag = false;
//						std::cout << "a: " << coefs[3 * (i + 1)] << "   b: " << coefs[3 * (i + 1) + 1] << "   c:" << coefs[3 * (i + 1) + 2] <<std::endl;
						break;
						
					}
					else {
						newvec[temp_index] = innerhash[i][l];
					}
				}
				if(collision_flag)
					innerhash[i] = newvec;
				prime_change++;
			}
		}
	}


	return true;
}

void HashTable::change_constants(int s,int size,int to_prime)
{
	
	coefs[s + 2] = find_next_prime(pow(to_prime,2));
	int powsize = pow(size, 2);
	coefs[s + 3] = rand() % powsize;
	coefs[s + 0] = rand()% powsize;
	coefs[s + 1] = rand()% powsize *rand()% powsize;
}

bool HashTable::hash(std::vector<std::vector<double>> numbers)
{
	if (numbers.size() < 1)
		return false;
	change_constants(0,sizev,sizev);

	for (int i = 0; i < sizev; i++) {
		int index = hashFunction(numbers[i], 0, sizev);
		innerhash[index].push_back(numbers[i]);
	}

	
	return perfect_rehash();
}

void HashTable::searchelem(std::vector<double> elem)
{
	int index1 = hashFunction(elem,0,sizev);
	int sizet = innerhash[index1].size();
	if (sizet == 0) {
		std::cout << '\n';
		std::cout << "No such vector" << '\n';
		std::cout << '\n';
		return;
	}
	int index2 = 0;
	if (sizet >1) {
		index2 = hashFunction(elem, 4*(index1+1), sizet);
	}
	
	if (sizet !=0 && innerhash[index1][index2] == elem) {
		std::cout << '\n';
		std::cout << "Vector is located at : ";
		std::cout << index1 << " " << index2;
		std::cout << '\n';
	}
	else {
		std::cout << '\n';
		std::cout << "No such vector! "<< '\n';
		std::cout << '\n';

	}

}

