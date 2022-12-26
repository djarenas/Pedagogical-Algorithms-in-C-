#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"

//Purpose: Custom Trie class. 
class Trie {
    TrieNode* root;

public:
    
    //Constructor.
    
    Trie();
    ~Trie();

    //METHODS

    void insert(string key);
    bool search(string target);
};

#endif