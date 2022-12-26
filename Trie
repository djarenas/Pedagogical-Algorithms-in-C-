#ifndef TRIENODE_H
#define TRIENODE_H

#include "TrieNode.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;

//Forward declarations
class Trie;

//Purpose: Nodes for the Trie class. 
//Each node has a letter, a boolean denoting whether it is a terminal (one of the stored words ends here), and 
//an unordered map. The unordered map contains the pointers to all the other nodes this node is linked to.
class TrieNode {
private:
    char letter;
    unordered_map <char, TrieNode*> childrenmap;
    bool terminal;

public:
    //Constructor, destructor
    
    TrieNode(char data);
    ~TrieNode();

    //Friends are a good thing.
    friend class Trie;
};

#endif
