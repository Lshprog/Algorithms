#pragma once

#include "ComplexNumber.h"


class AAtree {
	
	struct Node
	{
		ComplexNumber data;

		int level;
		Node* left;
		Node* right;
		Node* parent;

		Node(ComplexNumber data = NULL) {
			this->left = nullptr;
			this->right = nullptr;
			this->parent = nullptr;
			this->data = data;
			this->level = 1;
		}

		~Node() {
			delete this->left;
			delete this->right;
		}

	};

	Node* root;

	


public:
	AAtree() {
		this->root = nullptr;
	}
	~AAtree() {
		delete this->root;
	}

	Node* returnroot() {
		return this->root;
	}


	Node* skew(Node* node);
	Node* split(Node* node);
	Node* insert(ComplexNumber data,Node* node);
	Node* remove(ComplexNumber data, Node* node);
	Node* successor(Node* node);
	Node* predecessor(Node* node);
	Node* min_of_tree(Node* node);
	Node* max_of_tree(Node* node);
	Node* decrease_level(Node* node);
	int search(ComplexNumber data,Node* node);

	void printTreeOut(Node* node);

};