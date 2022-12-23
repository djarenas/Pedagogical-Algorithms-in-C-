#ifndef BINARYSEARCHTREELL_H
#define BINARYSEARCHTREELL_H

#include "BinaryTreeLL.h"

//Purpose: A derived class from Binary Tree. 
//Every node in the tree must have a value between the values of its leftchild and rightchild.
class BinarySearchTreeLL : public BinaryTreeLL {
public:

    //Constructor, Destructor
    
    BinarySearchTreeLL();
    ~BinarySearchTreeLL();

    //METHODS

    BTNode* insert (BTNode* cnode, const int data);
    void insert(const int data);
    void build(vector<int> v);
    bool search(BTNode* cnode, int target);
    bool search(int target);
    int findSmallestValue(BTNode* cnode);
    BTNode* remove(BTNode* cnode, int target);
    void remove(int target);
};

#endif