#ifndef GNODE_H
#define GNODE_H

#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::pair;
using std::queue;
using std::unordered_map;
using std::vector;

//Purpose: A node to be used for the graph class.
//Each node is named by a string.
//Utilizes an unordered map to be able to search for connections in O(1) average time.
class GNode {
  public:
    string name;
    unordered_map<string, GNode*> connections;

    //Constructor
    GNode(string name) {
        this->name = name;
    }

    //Destructor
    ~GNode() {
        //Make the node's connections all point to nullpointers
        auto x = connections.begin();
        while (x != connections.end()) {
            x->second = nullptr;
            x++;
        }
    }
};
#endif
