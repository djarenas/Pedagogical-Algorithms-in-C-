//Header guards
#ifndef BTNODE_H
#define BTNODE_H

#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::vector;

//Forward declarations
class BinaryTreeLL;
class BinarySearchTreeLL;

//Purpose: Stores an integer and the pointers to a left and right child.
class BTNode {
public:
    int data;
    BTNode* leftchild;
    BTNode* rightchild;

    //Constructor
    BTNode(int d);

    //Destructor: Recursively deletes dynamically-allocated memory in post-order transversal.
    ~BTNode();
};
#endif
