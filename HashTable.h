#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

class HashTable {
	std::vector<double>* innerhash;
	std::size_t sizev;
	int* coefs;
	int hashFunction(double key, int n,size_t size);
	bool perfect_rehash();
	void change_constants(int s,int size,int to_prime);
public:
	HashTable(std::vector<double>& vec);
	~HashTable() {
		delete []innerhash;
		delete []coefs;
	}
	void print();
	bool hash(std::vector<double> numbers);
	void searchelem(double elem);
};

void remove_duplicates(std::vector<double>& vec);