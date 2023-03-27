#include "AAtree.h"

AAtree::Node* AAtree::skew(Node* node)
{
    if (node == nullptr)
        return nullptr;
    else if (node->left == nullptr)
        return node;
    else if (node->level == (node->left)->level) {
        Node* temp = node->left;
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

AAtree::Node* AAtree::split(Node* node)
{
    if (node == nullptr)
        return nullptr;
    else if ((node->right == nullptr)||((node->right)->right == nullptr))
        return node;
    else if (node->level == (node->right)->right->level) {
        Node* temp = node->right;
        if (this->root == node)
            this->root = temp;
        temp->parent = node->parent;
        node->parent = temp;
        node->right = temp->left;
        if(node->right!=nullptr)
            (node->right)->parent = node;
        temp->left = node;
        temp->level++;
        return temp;
    }
    else
        return node;
}

AAtree::Node* AAtree::insert(ComplexNumber data,Node* node)
{
    if (node == nullptr) {
        node = new Node(data);
        if (this->root == nullptr)
            this->root = node;
        return node;
    }
    else if (compare_complex(data, node->data)==1) {
        node->right = insert(data, node->right);
        if (node->right != nullptr)
            (node->right)->parent = node;
    }
    else if (compare_complex(data, node->data)==0) {
        node->left = insert(data, node->left);
        if (node->left != nullptr)
            (node->left)->parent = node;
    }
    else {
        std::cout << "Such complex number already exists!"<<std::endl;
        return node;
    }

    //idea to avoid calls of skew and split in case such node exists

    node = skew(node);
    node = split(node);

    return node;
}

AAtree::Node* AAtree::remove(ComplexNumber data,Node* node)
{
    if (node == nullptr)
        return node;
    else if (compare_complex(data, node->data)==1) {
        node->right = remove(data,node->right);
        if(node->right!=nullptr)
            (node->right)->parent = node;
    }
    else if (compare_complex(data, node->data)==0) {
        node->left = remove(data, node->left);
        if (node->left != nullptr)
            (node->left)->parent = node;
    }
    else {
        if (node->left == nullptr && node->right == nullptr) {
            return nullptr;
        }
        else if (node->left == nullptr) {
            Node* temp = successor(node);
            node->right = remove(temp->data,node->right);
            if(node->right!=nullptr)
                node->right->parent = node;
           
            node->data = temp->data;
            delete temp;
        }
        else {
            Node* temp = predecessor(node);
            node->left = remove(temp->data,node->left);
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

AAtree::Node* AAtree::successor(Node* node)
{
    if (node->right != nullptr) {
        return min_of_tree(node->right);
    }
    
    Node* tempp = node->parent;
    Node* temp = node;
    while (tempp!=nullptr && tempp->right == temp) {
        temp = tempp;
        tempp = tempp->parent;
    }
    return tempp;
  
}

AAtree::Node* AAtree::predecessor(Node* node)
{
    if (node->left != nullptr) {
        return max_of_tree(node->left);
    }
    Node* tempp = node->parent;
    Node* temp = node;
    while (tempp != nullptr && tempp->left == temp) {
        temp = tempp;
        tempp = tempp->left;
    }
    return tempp;
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

AAtree::Node* AAtree::decrease_level(Node* node)
{   
    int newlevel = 1;

    if(node->right!=nullptr && node->left!=nullptr)
        newlevel+= std::min(node->right->level, node->left->level);
    else {
        
    }

    if (newlevel < node->level) {
        node->level = newlevel;
        if ((node->right!=nullptr) &&(newlevel < node->right->level))
            node->right->level = newlevel;
    }
    return node;

}

int AAtree::search(ComplexNumber data, Node* node)
{
    if (node == nullptr) {
        std::cout << "No such elem in the tree!" << std::endl;
        return NULL;
    }
    if (compare_complex(data, node->data)==1)
        return search(data,node->right);
    else if (compare_complex(data, node->data)==0)
        return search(data, node->left);
    else
        return node->level;
}

void AAtree::printTreeOut(Node* node)
{
    if (node != nullptr) {
        printTreeOut(node->left);
        std::cout << node->data.getRp() << " + i(" << node->data.getIp() << ") "<<"level: "<<node->level<<std::endl;
        printTreeOut(node->right);
    }
}
