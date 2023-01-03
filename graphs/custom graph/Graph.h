#ifndef GRAPH_H
#define GRAPH_H

#include "GNode.h"

//Purpose: A Graph of nodes and edges. Can be directed or undirected.
class Graph {
private:

    unordered_map<string, GNode*> nodemap;
    bool undirected;

public:

    //Constructor, Destructor

    Graph(vector<string> entries, bool undirected = true);
    ~Graph();

    //METHODS

    //Print each node and their connections.

    void printGraph();

    //Manipulate nodes and edges.

    void addNode (string name);
    bool doesNodeExist (string name);
    bool doesEdgeExist (string start_node, string end_node);
    void addEdge (string start_node, string end_node);
    void removeEdge(string start_node, string end_node, bool bilateral = false);
    void removeNode(string name);

    //Traverse the graph functions

    void updateQueue(GNode* cnode, queue<string> &q, unordered_map<string,bool> &explored);
    bool breadthFirstSearch(string root, string target);
    void recursiveDBSearch(string node, string target, unordered_map<string,bool> &explored, bool &found);
    bool depthFirstSearch(string root, string target);
};

#endif