#include "HashTable.h"

void remove_duplicates(std::vector<double>& vec)
{
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


HashTable::HashTable(std::vector<double>& vec) {
	remove_duplicates(vec);
	sizev = vec.size();
	innerhash = new std::vector<double>[sizev];
	coefs = new int[3 * (sizev + 1)];
	for (int i = 0; i < 3 * (sizev + 1); i++) {
		coefs[i] = 0;
	}
	srand(time(0));
}


int HashTable::hashFunction(double key,int s,size_t size)
{
	std::pair<int,int> value = reduction(key);
	int tempsize = size;
	int signindex = key > 0 ? 0 : 1;
	
	int index = ((abs(value.first) * coefs[0+s] + abs(value.second) * coefs[1+s]) % coefs[2+s]+signindex) % tempsize;

	/*std::cout << '\n';
	std::cout << coefs[0 + s] << " " << coefs[1 + s] << " " << coefs[2 + s] << " " << size << " " << value.first<<"    index: "<<index;
	std::cout << '\n';*/

	return index;
}

void HashTable::print()
{
	for (int i = 0; i < sizev; i++) {
		std::cout << i << ": ";
		int temp_size = innerhash[i].size();
		for (int j = 0; j < temp_size; j++) {
			if(innerhash[i][j]!=NULL)
				std::cout << innerhash[i][j] << " ";
		}
		std::cout << '\n';
	}

	std::cout << '\n';
	std::cout << '\n';
	int j = 0;
	for (int i = 0; i < 3 * (sizev + 1); i++) {
		if (i % 3 == 0) {
			std::cout << '\n';
			std::cout << "Coefs " << j << " : ";
			j++;
		}
		std::cout << coefs[i]<<" ";
		
	}
}

bool HashTable::perfect_rehash()
{
	for (int i = 0; i < sizev; i++) {
		if (innerhash[i].size() > 1) {
			bool collision_flag = false;
			int prime_change = 0;
			while (!collision_flag) {
				std::vector<double> newvec = std::vector<double>(innerhash[i].size() * innerhash[i].size());
				change_constants(3*(i+1),newvec.size(),innerhash[i].size()+prime_change);
				collision_flag = true;
				for (int l = 0; l < innerhash[i].size(); l++) {
					int temp_index = hashFunction(innerhash[i][l],3*(i+1),newvec.size());
					if (newvec[temp_index]!=NULL ) {
						collision_flag = false;
						std::cout << "a: " << coefs[3 * (i + 1)] << "   b: " << coefs[3 * (i + 1) + 1] << "   c:" << coefs[3 * (i + 1) + 2] <<std::endl;
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
	coefs[s + 0] = rand()%size;
	coefs[s + 1] = rand()%size*rand()%size;
}

bool HashTable::hash(std::vector<double> numbers)
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

void HashTable::searchelem(double elem)
{
	int index1 = hashFunction(elem,0,sizev);
	if (innerhash[index1].size() == 0) {
		std::cout << '\n';
		std::cout << "No such number" << '\n';
		std::cout << '\n';
		return;
	}
	int index2 = 0;
	if (innerhash[index1].size()>1) {
		index2 = hashFunction(elem, 3*(index1+1), innerhash[index1].size());
	}
	
	if (innerhash[index1].size()!=0 && innerhash[index1][index2] == elem) {
		std::cout << '\n';
		std::cout << "Number is located at : ";
		std::cout << index1 << " " << index2;
		std::cout << '\n';
	}
	else {
		std::cout << '\n';
		std::cout << "No such number! "<< '\n';
		std::cout << '\n';

	}

}

