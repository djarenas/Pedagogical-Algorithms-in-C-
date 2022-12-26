#include "TrieNode.h"

//Constructor
TrieNode::TrieNode(char data) {
    letter = data;
    terminal = false;
}

//Destructor.
//Must be able to recursively delete the nodes linked to this node.
TrieNode::~TrieNode() {
    cout << "Currently deleting: " << letter << endl;
    
    //Iterate through all the nodes that this node is connected to.
    unordered_map<char,TrieNode*>::iterator it;
    for (it = childrenmap.begin(); it != childrenmap.end(); ++it) {
        
        delete childrenmap[it->first];
    }
}

