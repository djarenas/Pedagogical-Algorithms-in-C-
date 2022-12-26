#include "Trie.h"

//Constructor
Trie::Trie() {
    //A new trie object has by default an empty root pointing to no other nodes.
    root = new TrieNode('\0');
}

//Destructor
Trie::~Trie() {
    //Deletes the root; the node destructor recursively deletes all the nodes connected to the root.
    delete root;
}

//Purpose: Inserts a new key word into the trie structure.
//O(key-length).
void Trie::insert(string key) {
    //Make a temporary node. Start at the root of the trie.
    TrieNode* cnode = root;
    
    //For every character in the key.
    for (auto c : key) {
        //If the letter is not contained in this node, add it to the character map of the node.
        if (cnode->childrenmap.count(c) == 0) {
            //Create a new node. Dynamically-allocated memory.
            TrieNode* n = new TrieNode(c);
            
            //Update the map of the current node so that it can direct to the new node.
            cnode->childrenmap[c] = n;
        }

        //Move the temporary node to the next node: The node containing the letter in this iteration.
        cnode = cnode->childrenmap[c];
    }
    
    //You are here because you are out of words, update the terminal boolean for this node.
    cnode->terminal = true;
}

//Purpose: Search the trie structure for a target word.
bool Trie::search(string target) {
    //Start from root.
    TrieNode* cnode = root;

    //For every character in the target.
    for (auto c : target) {
        //Return false if the character is not in the children map.
        if (cnode->childrenmap.count(c) == 0) {
            return false;
        }

        //If its present, then move to the node containing that character.
        cnode = cnode->childrenmap[c];
    }

    //You are here because you ran out of characters. 
    //For the target word to match, this node must be a terminal.
    return cnode->terminal;
}