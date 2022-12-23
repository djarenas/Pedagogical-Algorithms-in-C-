#include "BinaryTreeLL.h"

//Constructor
BinaryTreeLL::BinaryTreeLL() {
    root = nullptr;
}

//Destructor
BinaryTreeLL::~BinaryTreeLL() {
    if (root != nullptr) {
        //Utilize the BTNode Class Destructor and recursively delete the tree by starting from the root.
        delete root; 
        root = nullptr;
    }
}

//Getters

BTNode* BinaryTreeLL::getRoot() {
    return root;
}

//Purpose: Print binary tree in preorder-traversal: Root, left-subtree, right-subtree.
//Function overloaded to recursively print the subtree from a specific node.
void BinaryTreeLL::printPreOrder(BTNode* cnode) {
    //Base case: Empty node, return.
    if (cnode == nullptr) {
        return;
    }
    //Recursive case
    cout << cnode->data << " ";
    printPreOrder(cnode->leftchild);
    printPreOrder(cnode->rightchild);
}

//Purpose: Print binary tree in preorder-traversal: Root, left-subtree, right-subtree.
void BinaryTreeLL::printPreOrder() {
    cout << "Printing in pre-order: ";
    printPreOrder(root);
    cout << endl;
}

//Purpose: Print binary tree in in-order traversal: Left, root, right.
//Function overloaded to recursively print the subtree from a specific node.
void BinaryTreeLL::printInOrder(BTNode* cnode) {
    //Base case: Empty node, return.
    if (cnode == nullptr) {
        return;
    }
    //Recursive case
    printInOrder(cnode->leftchild);
    cout << cnode->data << " ";
    printInOrder(cnode->rightchild);
}

//Purpose: Print binary tree in in-order traversal: Left, root, right.
void BinaryTreeLL::printInOrder() {
    cout << "Printing in In-order: ";
    printInOrder(root);
    cout << endl;
}

//Purpose: Print binary tree in post-order traversal: Left, right, root.
//Function overloaded to recursively print the subtree from a specific node.
void BinaryTreeLL::printPostOrder(BTNode* cnode) {
    //Base case: Empty node, return.
    if (cnode == nullptr) {
        return;
    }
    //Recursive case
    printPostOrder(cnode->leftchild);
    printPostOrder(cnode->rightchild);
    cout << cnode->data << " ";
}

//Purpose: Print binary tree in post-order traversal: Left, right, root.
void BinaryTreeLL::printPostOrder() {
    cout << "Printing in post-order: ";
    printPostOrder(root);
    cout << endl;
}

//Purpose: Print binary tree in level-order traversal.
void BinaryTreeLL::printLevelOrder() {
    cout << "Printing in level-order: ";

    //Queue of node pointers.
    //Add the root as is always the first level by definition. Add nullptr.
    queue<BTNode*> qnodes; 
    qnodes.push(root);
    qnodes.push(nullptr);


    //Explore the queue of nodes until you run out of things to explore.
    while ( !qnodes.empty() ) {
        //The current node being explored in this iteration.
        BTNode* current = qnodes.front();
        
        //When the current node in the queue is a null...
        if ( current == nullptr ) {        
            qnodes.pop();

            //If the queue is empty, then you are done. Otherwise, add a null to denote levels.
            if ( !qnodes.empty() ) {
                qnodes.push(nullptr);
            }
        }
        
        //When the current node in the queue has data...
        else {
            //Print
            cout << current->data << " ";
            
            //If the node has any children, add them to the queue.
            if (current->leftchild != nullptr) {
                qnodes.push(current->leftchild);
            }
            if (current->rightchild != nullptr) {
                qnodes.push(current->rightchild);
            }
            
            //You are done exploring this node. Remove it from queue. 
            qnodes.pop();
        }
    }
    cout << endl;
}

//Purpose: Read an existing binary tree object and return a vector containing the tree data.
//Function overloaded to start from a specific node's subtree.
//Reading is performed in post-order traversal.
void BinaryTreeLL::readBinaryTree(BTNode* cnode, vector<int> &values) {
    //Base case: You reach a null node.
    if (cnode == nullptr) {
        return;
    }

    //Recursive case: Depth-first read.
    readBinaryTree(cnode->leftchild, values);
    readBinaryTree(cnode->rightchild, values);
    
    //Read current node and put it in the vector
    values.push_back(cnode->data);
}

//Purpose: Read an existing binary tree object and return a vector containing all the binary tree data.
//Output vector contains the binary tree elements in post-order.
vector<int> BinaryTreeLL::readBinaryTree () {
    vector<int> results = {};
    
    //Special case: The tree is empty. Return an empty vector.
    if (root == nullptr) {
        return results;
    }

    readBinaryTree(root, results);
    return results;
}

//Purpose: Calculate the height of the binary tree: One plus the maximum distance away from root.
//Function overloaded to start from a specific node and recursively calculate the heights of the subtrees.
int BinaryTreeLL::calcBinaryTreeHeight(BTNode* cnode) {
    //Base case: You reach a null.
    if (cnode == nullptr) {
        return 0;
    }

    //Recursive case: Calculate the heights of the subtrees
    
    int h1 = calcBinaryTreeHeight(cnode->leftchild);    //Left subtree height.
    int h2 = calcBinaryTreeHeight(cnode->rightchild);   //Right subtree height.

    //Return 1 + largest height of the two children-subtrees.
    return (1 + std::max(h1,h2));
}

//Purpose: Calculate the height of the binary tree. One plus the maximum distance away from root.
int BinaryTreeLL::calcBinaryTreeHeight() {
    return calcBinaryTreeHeight(root);
}



//Purpose: Count how many times a target-integer appears in the binary tree object.
//Function overloaded to recursively depth-first search, starting from a specific node ("cnode").
int BinaryTreeLL::countInPostOrder(BTNode* cnode, const int target) {
    //Base case: You reach a null node.
    if (cnode == nullptr) {
        return 0;
    }

    //Recursive case: Depth-first search.
    int l = countInPostOrder(cnode->leftchild, target);
    int r = countInPostOrder(cnode->rightchild, target);
    
    //If target found, return the combined children's results PLUS one more.
    if (target == cnode->data) {
        return (l + r + 1);
    }

    //Target not found, return the combined children's results.
    return (l + r);
}

//Purpose: Count how many times a target-integer appears in the binary tree object.
//Depth-first (post-order) traversal of the tree.
int BinaryTreeLL::countInPostOrder(const int target) {
    return countInPostOrder(root, target);
}

//Purpose: Count how many times a target-integer appears in the binary tree object.
//In-level traversal of the tree.
int BinaryTreeLL::countInLevelOrder(const int target) {
    int counts = 0;

    //Initialize the queue of nodes; add the root.
    queue<BTNode*> qnodes;
    qnodes.push(root);

    //Start from the root.
    BTNode* cnode = root;
    while( !qnodes.empty()) {
        //Check if the current node's data is equal to the target, if so update counts.
        if (cnode->data == target) {
            counts++;
        }
        
        //Add children of current node to the queue.
        if (cnode->leftchild != nullptr) {
            qnodes.push(cnode->leftchild);
        }
        if (cnode->rightchild != nullptr) {
            qnodes.push(cnode->rightchild);
        }

        //You are done exploring this node.
        qnodes.pop();

        //Move the current node to the first in queue.
        cnode = qnodes.front();
    }

    cout << endl;
    return counts;
}

//Purpose: Recursively builds a binary tree in preorder-traversal: Root, left, right.
//Function overloaded to start from a specific node ("cnode").
//  "v": Contains the data for the nodes in pre-order. "-1" signifies no subtree.
//  "i": Keeps track of the current element in "v". Modified in place.
BTNode* BinaryTreeLL::build(BTNode* cnode, const vector<int> &v, int &i) {
    //Base case #1: "-1" in input vector signals no more subtrees here.
    if (v[i] == -1) {
        return nullptr;
    }
    
    //Base case #2: No more elements left to insert into the tree.
    if (i >= v.size()) {
        return nullptr;
    }

    //Recursive case: Create a new node and call the recursion for the children.

    //Create dynamically-allocated memory. 
    //Designed to be deleted recursively by the BTNode Class destructor.
    BTNode* n = new BTNode(v[i]);

    //Root step of the preorder: Move the current node to that new node.
    cnode = n;
    
    //Recursive call on the last two steps (left, right) of the preorder sequence.
    cnode->leftchild = build(cnode->leftchild, v, ++i);
    cnode->rightchild = build(cnode->rightchild, v, ++i);

    return cnode;
}

//Purpose: Build a binary tree using input from a vector.
//Input vector: Contains the data for the nodes in pre-order (root, left, right); "-1" element signifies no subtree.
void BinaryTreeLL::build(vector<int> v) {
    int i = 0;
    //The overloaded function will recursively build the tree.
    root = build(root, v, i);
}

//Purpose: Checks that each node's subtrees have heights that differ by no more than 1.
//Function overloaded to start from a specific node "cnode".
//Returns the height of the current node if subtrees are balanced.
//If the current node is not balanced, or one of its subtrees were not balanced, returns -1.
int BinaryTreeLL::checkTreeBalance(BTNode* cnode) {
    //Base case: You reach a null node. It is balanced by definition.
    if (cnode == nullptr) {
        return 0;
    }

    //Recursive cases

    //Get the height of the left-subtree.
    //If the left-subtree is unbalanced -> no further work needed and return -1.
    int left_height = checkTreeBalance(cnode->leftchild);
    if (left_height == -1) {
        return -1;
    }

    //Repeat for right-subtree.
    int right_height = checkTreeBalance(cnode->rightchild);
    if (right_height == -1) {
        return -1;
    }

    //Compare the left and right heights.
    //Return -1 if the difference is more than 1.
    //Otherwise, return the height of this node's subtree.
    int diff = abs(left_height - right_height);
    if (diff > 1) {
        return -1;
    }
    
    return (std::max(left_height, right_height) + 1);
}

//Purpose: Checks that each node's subtrees have heights that differ by no more than 1.
int BinaryTreeLL::checkTreeBalance() {
    return checkTreeBalance(root);
}


//Purpose: Searches the tree for the node closest to the root that holds the target data. 
//Returns the node-pointer and its parent node as a pair. 
//If target is found, returns {Parent-node*, node*}. 
//If target is found at root, returns {nullpointer, root}.
//If target not found: return pair of nullpointers.
pair<BTNode*,BTNode*> BinaryTreeLL::findNode(int target) {
    //Special case: Target is found at the root.
    if (root->data == target) {
        return {nullptr,root};
    }
    
    //Initialize a queue of nodes for the breadth-first search algorithm.
    //Make a temporary node that will start from the root. Add to queue.
    queue<BTNode*> qnodes;
    BTNode* cnode = root;
    qnodes.push(cnode);

    //BFS algorithm
    while(!qnodes.empty()) {

        //Check if leftchild has the target; 
        //if so return the current node and the specific child.
        if (cnode->leftchild != nullptr && cnode->leftchild->data == target) {
            return {cnode, cnode->leftchild};
        }
        //Check rightchild...
        if (cnode->rightchild != nullptr && cnode->rightchild->data == target) {
            return {cnode, cnode->rightchild};
        }

        //The target was not found. Continue the BFS algorithm.
        
        //Add existing children of the current node to the queue.
        if (cnode->leftchild != nullptr) {
            qnodes.push(cnode->leftchild);
        }
        if (cnode->rightchild != nullptr) {
            qnodes.push(cnode->rightchild);
        }

        //You are done exploring this node.
        qnodes.pop();

        //Move the current node to the first in queue.
        cnode = qnodes.front();      
    }

    //The queue is empty, you explored all elements, you did not find the target.
    return {nullptr, nullptr};
}

//Purpose: Rotate the root either right (default) or left.
void BinaryTreeLL::rotateRoot(bool right = true) {
    //Special case: The tree is empty.
    if (root == nullptr) {
        cout << "Error in rotate. The root was null. No operation was carried." << endl;
        return;
    }

    //Right rotate.
    if (right) {
        BTNode* a = root;
        BTNode* b = root->leftchild;
        a->leftchild = b->rightchild;
        b->rightchild = a;
    }
    
    //Left rotate.
    BTNode* a = root;
    BTNode* b = root->rightchild;
    a->rightchild = b->leftchild;
    b->leftchild = a;
}

//Purpose: Right-rotate around specific node.
//Requires the pointer to the parent as well.
//Right-rotation requires that the node has a left-child.
void BinaryTreeLL::rightRotateNode(BTNode* parent, BTNode* cnode) {
    //Special case: The node asked to rotate is the root.
    if (cnode == root) {
        rotateRoot();
        return;
    }

    //Error case: The node asked to rotate, or its parent, is null.
    if (cnode == nullptr || parent == nullptr) {
        cout << "Error in rotate. The node was null. No operation was carried." << endl;
        return;
    }

    //Error case: The node does not have a left child.
    if (cnode->leftchild == nullptr) {
        cout << "Error in rightRotateNode."<< endl;
        cout << "Node selected: " << cnode->data << "." << endl;
        cout << "Right rotation requires that the node has a left child. No action performed." << endl;
        return;
    }

    //Figure out whether the current node is the left or right child of the parent.
    bool leftbranch = parent->leftchild == cnode;

    //Rotate
    BTNode* a = cnode;
    BTNode* b = cnode->leftchild;
    a->leftchild = b->rightchild;
    b->rightchild = a;
    
    //Since B is now above A, make parent node point to B.
    if (leftbranch) parent->leftchild = b;
    else parent->rightchild = b;
}

//Purpose: Left-rotate around specific node.
//Requires the pointer to the parent as well.
//Left-rotation requires that the node has a right-child.
void BinaryTreeLL::leftRotateNode(BTNode* parent, BTNode* cnode) {
    //Special case: The node asked to rotate is the root.
    if (cnode == root) {
        rotateRoot();
        return;
    }

    //Error case: The node asked to rotate, or its parent, is null.
    if (cnode == nullptr || parent == nullptr) {
        cout << "Error in rotate. The node was null. No operation was carried." << endl;
        return;
    }

    //Error case: The node does not have a rightchild.
    if (cnode->rightchild == nullptr) {
        cout << "Error in leftRotateNode."<< endl;
        cout << "Node selected: " << cnode->data << "." << endl;
        cout << "Left rotation requires that the node has a right child. No action performed." << endl;
        return;
    }

    //Figure out whether the current node is the left or right child of the parent.
    bool leftbranch = parent->leftchild == cnode;

    //Rotate
    BTNode* a = cnode;
    BTNode* b = cnode->rightchild;
    a->rightchild = b->leftchild;
    b->leftchild = a;
    
    //Since B is now above A, make parent node point to B.
    if (leftbranch) parent->leftchild = b;
    else parent->rightchild = b;
}