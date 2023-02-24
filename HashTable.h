#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

class HashTable {//Клас хеш-таблиця
	std::vector<double>* innerhash;//Масив векторів дійсних чисел який буде потім слугувати як під хеш-таблиця
	std::size_t sizev;//Розмір головної хеш-таблиці
	int* coefs;//Масив у якому будуть зберігатися усі константи для усіх хеш-таблиць

	int hashFunction(double key, int n,size_t size);//Хеш функція
	bool perfect_rehash();//Функція створення під хеш-таблиць при надобності
	void change_constants(int s,int size,int to_prime);//Зміна констант a,b,p
public:
	HashTable(std::vector<double>& vec);//Конструктор класу 
	~HashTable();//
	void print();//Виведення хеш-таблиці
	bool hash(std::vector<double> numbers);//Основна функція яка починає алгоритм хешування
	void searchelem(double elem);//Функція пошуку елемента у хеш-таблиці
};

void remove_duplicates(std::vector<double>& vec); //Функція видалення дублікатів з масиву
std::pair<int, int> reduction(double number);//Функція розділення дійсного числа на 2 цілих
bool isPrime(int val);//Перевірка числа на простоту
int find_next_prime(int val);//Пошук наступного простого числа