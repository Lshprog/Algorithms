#include "AAtree.h"

AAtree::Node* AAtree::skew(Node* node)
{
    if (node == nullptr)
        return nullptr;
    else if (node->left == nullptr)
        return node;
    else if (node->level == (node->left)->level) {
        Node* temp = node->left;
        temp->parent = node->parent;
        node->parent = temp;
        node->left = temp->right;
        (node->left)->parent = node;
        temp->right = node;
        return temp;
    }
    else
        return node;
}

AAtree::Node* AAtree::split(Node* node)
{
    if (node == nullptr)
        return nullptr;
    else if ((node->right == nullptr)||((node->right)->right == nullptr))
        return node;
    else if (node->level == (node->right)->right->level) {
        Node* temp = node->right;
        temp->parent = node->parent;
        node->parent = temp;
        node->right = temp->left;
        (node->right)->parent = node;
        temp->left = node;
        temp->level++;
        return temp;
    }
    else
        return node;
}

AAtree::Node* AAtree::insert(ComplexNumber* data,Node* node)
{
    if (node == nullptr) {
        node = new Node(data);
        return node;
    }
    else if ((compare_complex(data, this->root->data))) {
        node->right = insert(data, node->right);
        (node->right)->parent = node;
    }
    else if (!(compare_complex(node->data, this->root->data))) {
        node->left = insert(data, node->left);
        (node->left)->parent = node;
    }
    else {
        std::cout << "Such complex number already exists!";
        return node;
    }

    //idea to avoid calls of skew and split in case such node exists

    node = skew(node);
    node = split(node);

    return node;
}

AAtree::Node* AAtree::remove(ComplexNumber* data)
{

    return false;
}

AAtree::Node* AAtree::successor(Node* node)
{
    if (node->right != nullptr) {
        return min_of_tree(node);
    }

  
}

AAtree::Node* AAtree::predecessor(Node* node)
{
    return nullptr;
}

AAtree::Node* AAtree::min_of_tree(Node* node)
{
    Node* temp = node;
    while (temp->left != nullptr)
        temp = temp->left;
    return temp;
}

AAtree::Node* AAtree::max_of_tree(Node* node)
{
    Node* temp = node;
    while (temp->right != nullptr)
        temp = temp->right;
    return temp;
}
