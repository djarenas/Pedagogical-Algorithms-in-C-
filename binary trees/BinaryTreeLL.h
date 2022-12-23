#ifndef BINARYTREELL_H
#define BINARYTREELL_H

#include "BTNode.h"

using std::pair;

//Purpose: Binary Tree implemented from linked lists.
//It can be complete/incomplete and have any (or lack of) relationship between the ascendants and descendants.
class BinaryTreeLL {

protected:
    BTNode* root; //A pointer to the root of the tree.

public:
    //Constructors, Destructors, Getters

    BinaryTreeLL();
    ~BinaryTreeLL();
    BTNode* getRoot();

    //METHODS

    //Print functions, in different traversal orders.
    
    void printPreOrder(BTNode* cnode); 
    void printPreOrder();    
    void printInOrder(BTNode* cnode);
    void printInOrder();
    void printPostOrder(BTNode* cnode);
    void printPostOrder();
    void printLevelOrder();

    //Read an existing tree; calculate height; count how many times a particular element is found;
    //find a node that holds the data you want.

    void readBinaryTree(BTNode* cnode, vector<int> &values);
    vector<int> readBinaryTree ();
    int calcBinaryTreeHeight(BTNode* cnode);
    int calcBinaryTreeHeight();
    int countInPostOrder(BTNode* cnode, const int target);
    int countInPostOrder(const int target);
    int countInLevelOrder(const int target);
    
    //Build the binary tree using a vector.
    //Check Tree balance; rotate (left,right) around a node.
    
    BTNode* build(BTNode* cnode, const vector<int> &v, int &i);
    void build(vector<int> v);
    int checkTreeBalance(BTNode* cnode);
    int checkTreeBalance();
    pair<BTNode*,BTNode*> findNode(int target); 
    void rotateRoot(bool right);
    void rightRotateNode(BTNode* parent, BTNode* cnode);
    void leftRotateNode(BTNode* parent, BTNode* cnode);
};

#endif

 