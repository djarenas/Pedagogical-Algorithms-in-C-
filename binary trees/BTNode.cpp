#include "BTNode.h"

//Constructor
BTNode::BTNode(int d) {
    data = d;
    leftchild = nullptr;
    rightchild = nullptr;
}

//Destructor: Recursively deletes dynamically-allocated memory in post-order transversal.
BTNode::~BTNode() {
    delete leftchild; //Recursively deletes the left subtree.
    delete rightchild; //Recursively deletes the right subtree.
    cout << "Deleting Node: " << data << " at" << &data << endl; //Could act as an alert for some programming bugs.
}
