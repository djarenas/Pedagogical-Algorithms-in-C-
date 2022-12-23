#include "BinarySearchTreeLL.h"

//Constructor
BinarySearchTreeLL::BinarySearchTreeLL() {
    root = nullptr;
}

//Destructor
BinarySearchTreeLL::~BinarySearchTreeLL() {
    if (root != nullptr) {
        //Utilize the BTNode Class destructor to recursively deletes the tree.
        delete root; 
        
        root = nullptr;
    }
}

//Purpose: Insert a new node at the appropriate position of the binary search tree.
//Binary Search Tree: Left child must have a smaller value than the node; right child must have larger value.
//Function overloaded to start from a specific node.
BTNode* BinarySearchTreeLL::insert (BTNode* cnode, const int data) {
    //Base case: This node does not exist. Create it and return the pointer.
    if (cnode == nullptr) {
        cnode = new BTNode(data);
        return cnode;
    }

    //Recursive cases: The element to be inserted must be checked against the current data in the node.
    
    //If equal or less than the current element.
    //Recursively use this function on the left-child.
    if (data <= cnode->data) {
        cnode->leftchild = insert(cnode->leftchild, data);
    }

    //If more than the current element.
    //Recursively use this function on the right-child.
    if (data > cnode->data) {
        cnode->rightchild = insert(cnode->rightchild, data);
    }

    return cnode;
}

//Purpose: Insert a new node at the appropriate position of the binary search tree.
//Binary Search Tree: Left child must have a smaller value than the root; right child value must be larger.
void BinarySearchTreeLL::insert(const int data) {
    //Special case: The binary search tree is empty.
    if (root == nullptr) {
        root = insert(root, data);
        return;
    }

    insert(root, data);
}

//Purpose: Builds a binary search tree using input elements from a vector.
//Polymorphism: BinarySearchTreeLL objects will use this function over their base class equivalent.
void BinarySearchTreeLL::build(vector<int> v) {
    vector<int>::iterator vit = v.begin();
    while ( vit!=v.end() ) {
        insert(*vit);
        *vit++;
    }
}

//Purpose: Searches the binary search tree and returns a boolean on whether a particular value is found.
//Function overloaded to start from a specific node.
bool BinarySearchTreeLL::search(BTNode* cnode, int target) {
    //Base case #1: You reach a null
    if (cnode == nullptr) {
        return false;
    }

    //Base case #2: You find the target
    if (cnode->data == target) {
        return true;
    }

    //Recursive case: You gotta keep looking
    
    if (target < cnode->data) {
        return search(cnode->leftchild, target);
    }

    if (target > cnode->data) {
        return search(cnode->rightchild, target);
    }

    return false;
}

//Purpose: Searches the binary search tree and returns a boolean on whether a particular value is found.
//O(height).
bool BinarySearchTreeLL::search(int target) {
    return search(root, target);
}

//Purpose: Returns the smallest value contained in the binary search tree.
//O(height).
int BinarySearchTreeLL::findSmallestValue(BTNode* cnode) {
    while (cnode->leftchild != nullptr) {
        cnode = cnode->leftchild;
    }
    return cnode->data;
}

//Purpose: Finds and removes the farthest node containing a particular data and removes the node.
//Function overloaded to start from a specific node.
BTNode* BinarySearchTreeLL::remove(BTNode* cnode, int target) {
    //Base case #1: Nothing on this node.
    if (cnode == nullptr){
        return nullptr;
    }

    //Recursion cases: 

    if (target < cnode->data) {
        cnode->leftchild = remove(cnode->leftchild, target);
    }
    else if (target > cnode->data) {
        cnode->rightchild = remove(cnode->rightchild, target);
    }

    //If the target is found in this node...
    else if (target == cnode->data) {
        //The removal algorithm will differ based on the number of children the node has.
        
        //If the target is on a leaf node...
        if (cnode->leftchild == nullptr && cnode->rightchild == nullptr) {
            delete cnode;
            cnode = nullptr;
        }
        
        //If the target only has one child...
        else if (cnode->leftchild == nullptr || cnode->rightchild == nullptr) {
            //Find the child that is not empty.
            BTNode* child;
            if (cnode->leftchild == nullptr) {
                child = cnode->rightchild;
            }
            else {
                child = cnode->leftchild;
            }

            //Make a temporary node so you know where to delete.
            BTNode* temp = cnode;

            //Make the current node point to the child node.
            cnode = child;

            //Delete the old node.
            temp->leftchild = nullptr;
            temp->rightchild = nullptr;
            delete temp;
        }
        
        //If the target has two children...
        else {
            //Replace the value of this node with the smallest value in the right subtree,
            //and delete the node that used to hold the smallest value.

            //Find the smallest value of the tree.
            int min = findSmallestValue(cnode->rightchild);

            //Set the value of this node to be that value.
            cnode->data = min;

            remove(cnode->rightchild, min);
        }
    }

    return cnode;
}

//Purpose: Finds and removes the farthest node containing a particular data and removes the node.
void BinarySearchTreeLL::remove(int target) {
    root = remove(root, target);
}
