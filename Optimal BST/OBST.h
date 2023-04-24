#pragma once
#include "..\AA_tree_complexnumbers\AAtree.h"
#include <vector>

template <typename DataType>
class OBST :public BST<Node<DataType>>{
public:
	//Конструктор класу
	OBST(std::vector<std::pair<DataType,int>>& invec) {
		
		int len = invec.size();

		if (len == 0)
			std::cout << "Empty tree" << std::endl;

		else {
			costtable = new int* [len + 1];
			roottable = new int* [len];

			for (int i = 0; i <= len; i++) {
				costtable[i] = new int[len + 1];
				costtable[i][i] = 0;
				if (i < len) {
					costtable[i][i + 1] = invec[i].second;
					roottable[i] = new int[len];
					roottable[i][i] = i;
				}
			}

			this->len = len;

			calculateOptimum();
			this->root = constructTree(invec, 0, len - 1);

			//this->printTreeOut(this->root);
			std::cout << "Cost: " << costtable[0][len]<<std::endl;
			std::cout << std::endl;

			this->print(this->root);
		}
	}

	//Деструктор класу
	~OBST() {
		if (len != 0) {
			for (int i = 0; i <= len; i++) {
				delete[]costtable[i];
				if (i < len)
					delete[]roottable[i];
			}
		}
		delete []costtable;
		delete []roottable;

	}

	//Функція заповнення таблиць
	void calculateOptimum() {

		for (int d = 1; d < this->len; d++) {
			for (int i = 0; i < this->len - d; i++) {
				int j = d + i + 1;
				int min = INT_MAX;

				for (int l = i; l < j; l++) {
					int q = costtable[i][l] + costtable[l+1][j];
					if (q < min) {
						min = q;
						roottable[i][j-1] = l;
					}
				}

				int sum = 0;
				for (int t = i; t < j; t++) {
					sum+=costtable[t][t+1];
				}

				costtable[i][j] = min + sum;
			}
		}


	}

	//Функція побудови дерева за таблицею
	Node<DataType>* constructTree(std::vector<std::pair<DataType, int>>& invec,int lefts, int rights) {

		int index = roottable[lefts][rights];

		Node<DataType>* node = new Node<DataType>(invec[index].first);

		if (lefts == rights) {
			return node;
		}
		if (index != rights) {
			node->right = constructTree(invec,index+1,rights);
			if (node->right != nullptr)
				node->right->parent = node;
		}
		if (index != lefts) {
			node->left = constructTree(invec, lefts, index-1);
			if (node->left != nullptr)
				node->left->parent = node;
		}
		
		return node;


	}


	private:
		int len;//Кількість елементів у вхідному масиві.
		int** costtable;//таблиця цін
		int** roottable;//таблиця коренів


};

