#pragma once

#include "ComplexNumber.h"

template<typename DataType>
class Node {
public:
	Node* left;
    Node* right;
    Node* parent;
	DataType data;

    Node() {
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
    }

	//Коструктор вершини
	Node(DataType data = NULL) {
		this->left = nullptr;
		this->right = nullptr;
		this->parent = nullptr;
		this->data = data;
	}
	//Деструктор вершини
	~Node() {
        
	}
};


template<typename DataType>
class ANode//Клас вершини дерева
{
public:
    ANode* left;
    ANode* right;
    ANode* parent;
    DataType data;
    int level; //Рівень вершини

    ANode(){
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
    };
    //Коструктор вершини
    ANode(DataType data = NULL){
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        this->data = data;
        this->level = 1;
    }
    //Деструктор вершини
    ~ANode() {
        
    }
};


template<typename NodeType>
class BST {
public:
	BST() {
		this->root = nullptr;
	}

    void deleteTree(NodeType* node) {
        if (node != nullptr) {
            if(node->left!=nullptr)
                deleteTree(node->left);
            if(node->right!=nullptr)
                deleteTree(node->right);
            delete node;
        }
    }

	//Деструктор дерева
	virtual ~BST() {
        deleteTree(this->root);
	}

	//Функція повернення кореня дерева
	NodeType* returnroot() {
		return this->root;
	}
    //Функція вставки 
    NodeType* insert(NodeType* toadd, NodeType* node) {
        if (node == nullptr) {
            node->data = toadd->data;
            if (this->root == nullptr)
                this->root = node;
            return node;
        }
        else if (toadd->data > node->data) {
            node->right = insert(toadd, node->right);
            if (node->right != nullptr)
                (node->right)->parent = node;
        }
        else if (toadd->data < node->data) {
            node->left = insert(toadd, node->left);
            if (node->left != nullptr)
                (node->left)->parent = node;
        }
        else {
            std::cout << "Such data already exists!" << std::endl;
            return node;
        }

        return node;
    } 

    //Функція видалення
    NodeType* remove(NodeType* toremove, NodeType* node) {
        if (node == nullptr)
            return node;
        else if (toremove->data > node->data) {
            node->right = remove(toremove, node->right);
            if (node->right != nullptr)
                (node->right)->parent = node;
        }
        else if (toremove->data < node->data) {
            node->left = remove(toremove, node->left);
            if (node->left != nullptr)
                (node->left)->parent = node;
        }
        else {
            if (node->left == nullptr && node->right == nullptr) {
                return nullptr;
            }
            else if (node->left == nullptr) {
                NodeType* temp = successor(node);
                node->right = remove(temp, node->right);
                if (node->right != nullptr)
                    node->right->parent = node;

                node->data = temp->data;
                delete temp;
            }
            else {
                Node* temp = predecessor(node);
                node->left = remove(temp, node->left);
                if (node->left != nullptr)
                    node->left->parent = node;
                node->data = temp->data;

                delete temp;
            }
        }

        return node;
    } 

    //Функція пошуку наступника
    NodeType* successor(NodeType* node) {
        if (node->right != nullptr) {
            return min_of_tree(node->right);
        }

        NodeType* tempp = node->parent;
        NodeType* temp = node;
        while (tempp != nullptr && tempp->right == temp) {
            temp = tempp;
            tempp = tempp->parent;
        }
        return tempp;
    }

    //Функція пошуку попередника
    NodeType* predecessor(NodeType* node){
        if (node->left != nullptr) {
            return max_of_tree(node->left);
        }
        NodeType* tempp = node->parent;
        NodeType* temp = node;
        while (tempp != nullptr && tempp->left == temp) {
            temp = tempp;
            tempp = tempp->left;
        }
        return tempp;
    }

    //Пошук мінімума 
    NodeType* min_of_tree(NodeType* node) {
        NodeType* temp = node;
        while (temp->left != nullptr)
            temp = temp->left;
        return temp;
    }

    //Пошук максимума 
    NodeType* max_of_tree(NodeType* node) {
        NodeType* temp = node;
        while (temp->right != nullptr)
            temp = temp->right;
        return temp;
    }

    //Пошук елемента
    int search(NodeType* tosearch, NodeType* node) {
        if (node == nullptr) {
            std::cout << "No such elem in the tree!" << std::endl;
            return NULL;
        }
        if (tosearch->data > node->data)
            return search(tosearch, node->right);
        else if (tosearch->data < node->data)
            return search(tosearch, node->left);
        else
            return 1;
    } 

    //Вивід дерева
    virtual void printTreeOut(NodeType* node) {
        if (node != nullptr) {
            printTreeOut(node->left);
            std::cout << node->data << std::endl;
            printTreeOut(node->right);
        }
    } 

    void print(const std::string& prefix, const NodeType* node, bool isLeft, bool isRoot)
    {
        if (node != nullptr)
        {
            std::cout << prefix;

            if (!isRoot)
                std::cout << (isLeft ? "L|---" : "R|----");

            else std::cout << "|---";

            // print the value of the node
            std::cout << node->data << std::endl;

            // enter the next tree level - left and right branch
            print(prefix + (isLeft ? "|   " : "    "), node->left, true, false);
            print(prefix + (isLeft ? "|   " : "    "), node->right, false, false);
        }
    }

    void print(const NodeType* node)
    {
        print("", node, false, true);
    }


   public:
       NodeType* root;


};



template<typename DataType>
class AAtree:public BST<ANode<DataType>> { //Клас АА-дерево
	
public:

    //Функція skew
    ANode<DataType>* skew(ANode<DataType>* node) {

        if (node == nullptr)
            return nullptr;
        else if (node->left == nullptr)
            return node;
        else if (node->level == (node->left)->level) {
            ANode<DataType>* temp = node->left;
            if (this->root == node)
                this->root = temp;
            temp->parent = node->parent;
            node->parent = temp;
            node->left = temp->right;
            if (node->left != nullptr)
                (node->left)->parent = node;
            temp->right = node;
            return temp;
        }
        else
            return node;

    } 

    //Функція split
    ANode<DataType>* split(ANode<DataType>* node) {
        if (node == nullptr)
            return nullptr;
        else if ((node->right == nullptr) || ((node->right)->right == nullptr))
            return node;
        else if (node->level == (node->right)->right->level) {
            ANode<DataType>* temp = node->right;
            if (this->root == node)
                this->root = temp;
            temp->parent = node->parent;
            node->parent = temp;
            node->right = temp->left;
            if (node->right != nullptr)
                (node->right)->parent = node;
            temp->left = node;
            temp->level++;
            return temp;
        }
        else
            return node;
    }

    //Функція пониження рівня
    ANode<DataType>* decrease_level(ANode<DataType>* node) {
        int newlevel = 1;

        if (node->right != nullptr && node->left != nullptr)
            newlevel += std::min(node->right->level, node->left->level);
        else {

        }

        if (newlevel < node->level) {
            node->level = newlevel;
            if ((node->right != nullptr) && (newlevel < node->right->level))
                node->right->level = newlevel;
        }
        return node;
    } 
	
    //Функція вставки 
    ANode<DataType>* insert(DataType data, ANode<DataType>* node)  {
        if (node == nullptr) {
            node = new ANode<DataType>(data);
            if (this->root == nullptr)
                this->root = node;
            return node;
        }
        else if (data > node->data) {
            node->right = insert(data, node->right);
            if (node->right != nullptr)
                (node->right)->parent = node;
        }
        else if (data < node->data) {
            node->left = insert(data, node->left);
            if (node->left != nullptr)
                (node->left)->parent = node;
        }
        else {
            std::cout << "Such complex number already exists!" << std::endl;
            return node;
        }

        //idea to avoid calls of skew and split in case such node exists

        node = skew(node);
        node = split(node);

        return node;
    } 
    //Функція видалення
    ANode<DataType>* remove(DataType data, ANode<DataType>* node) {
        if (node == nullptr)
            return node;
        else if (data > node->data) {
            node->right = remove(data, node->right);
            if (node->right != nullptr)
                (node->right)->parent = node;
        }
        else if (data < node->data) {
            node->left = remove(data, node->left);
            if (node->left != nullptr)
                (node->left)->parent = node;
        }
        else {
            if (node->left == nullptr && node->right == nullptr) {
                return nullptr;
            }
            else if (node->left == nullptr) {
                ANode<DataType>* temp = this->successor(node);
                node->right = remove(temp->data, node->right);
                if (node->right != nullptr)
                    node->right->parent = node;

                node->data = temp->data;
                delete temp;
            }
            else {
                ANode<DataType>* temp =this->predecessor(node);
                node->left = remove(temp->data, node->left);
                if (node->left != nullptr)
                    node->left->parent = node;
                node->data = temp->data;

                delete temp;
            }
        }

        node = decrease_level(node);
        node = skew(node);
        node->right = skew(node->right);
        if (node->right != nullptr) {
            (node->right)->right = skew((node->right)->right);
        }

        node = split(node);
        node->right = split(node->right);

        return node;
    }

    
    void printTreeOut(ANode<DataType>* node) override {
        if (node != nullptr) {
            printTreeOut(node->left);
            std::cout << node->data <<"  |  level:" << node->level << std::endl;
            printTreeOut(node->right);
        }
    }
};

