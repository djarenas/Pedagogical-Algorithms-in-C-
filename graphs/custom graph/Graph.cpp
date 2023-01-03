#include "Graph.h"

//Constructor
//Requires a vector of strings with all the entries you want to start with in the graph.
Graph::Graph(vector<string> entries, bool undirected) {
    
    //Set directionality of the graph.
    this->undirected = undirected;
    
    //Iterate through all entries.
    vector<string>::iterator it = entries.begin();
    while (it != entries.end()) {
        //Dynamically allocated memory. Designed to be deleted in the Graph destructor.
        nodemap[*it] = new GNode(*it); 
        it++;
    }
}

//Destructor
//Deletes the dynamically allocated memory of each node in the graph.
Graph::~Graph() {
    auto x = nodemap.begin();
    
    while (x != nodemap.end()) {
        cout << "Delete: " << x->first << endl;
        delete x->second; //Recovers the memory that was dynamically allocated.
        x = nodemap.erase(x); //Restoring the memory
    }
}

//Purpose: Print the graph so that you show each connection of every node.
void Graph::printGraph() {
    //Iterate through all entries stored in the Graph's unordered-map.
    for (auto x = nodemap.begin(); x != nodemap.end(); x++) {
        cout << x->first << ": ";
        
        //Get the node pointer using the unordered map.
        GNode* n = x->second;

        //Iterate through all the connections in this node.
        for (auto it = (n->connections).begin(); it != (n->connections).end(); it++) {
            cout << it->first << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//Purpose: Add a single node to the Graph object.
//O(1) in average.
void Graph::addNode(string name) {
    //Pointer to new node is stored in the Graph's unordered-map.
    nodemap[name] = new GNode(name); //Dynamically-allocated memory. Destroyed in the Graph destructor.
    return;
}

//Purpose: Checks if the node exists.
bool Graph::doesNodeExist(string name) {
    return !(nodemap.find(name) == nodemap.end());
}

//Purpose: Unidirectionally checks if there is an edge between two nodes.
//O(1) on average.
bool Graph::doesEdgeExist(string start_node, string end_node)  {
    //Check that the start and end nodes exist; if not, print an error and return it does not exist.
    if (!doesNodeExist(start_node)) {
        cout << "Error in doesEdgeExist. There is no node: " << start_node << ". Terminating." << endl; 
        return false;
    }
    if (!doesNodeExist(end_node)) {
        cout << "Error in doesEdgeExist. There is no node: " << end_node << ". Terminating." << endl;
        return false;
    }

    //Check that the start_node has the end_node in its connections.
    return !( (nodemap[start_node]->connections).find(end_node) == (nodemap[start_node]->connections).end() );
}

//Purpose: Add a new connection to a specific node.
//O(1) in average.
//Throws error if either node does not exist yet.
void Graph::addEdge(string start_node, string end_node) {

    //Check that the start and end nodes exist; if not, throw an error.
    if (!doesNodeExist(start_node)) {
        cout << "Error in addEdge. There is no node: " << start_node << ". Terminating." << endl; 
        return;
    }
    if (!doesNodeExist(end_node)) {
        cout << "Error in addEdge. There is no node: " << end_node << ". Terminating." << endl;
        return;
    }

    //Update the connections of the node. O(1) in average.
    //Right side gets the pointer to the end node.
    //Left side updates the connections-map of the start node.
    (nodemap[start_node]->connections)[end_node] = nodemap[end_node];

    //Special case for undirected map. The edge must be connected in the other direction as well.
    if (undirected) {
        (nodemap[end_node]->connections)[start_node] = nodemap[start_node];
    }
}

//Purpose: Remove edge. Keep the nodes intact. Unilateral or bilateral option.
//O(1) on average.
void Graph::removeEdge(string start_node, string end_node, bool bilateral) {
    //Check that the start- and end-node exist; if not, throw an error.
    if (!doesNodeExist(start_node)) {
        cout << "Error in removeEdge. There is no node: " << start_node << ". Terminating." << endl; 
        return;
    }
    if (!doesNodeExist(end_node)) {
        cout << "Error in removeEdge. There is no node: " << end_node << ". Terminating." << endl;
        return;
    }

    //Unilateral deletion of the edge.
    (nodemap[start_node]->connections).erase(end_node);

    //Special case: Bidirectional graph AND you want to remove bidirectional edge
    if(undirected) {
        if (bilateral) {
            (nodemap[end_node]->connections).erase(start_node);
        }
    }
}

//Purpose: Remove node from the graph. Connections of the other nodes are updated.
//O(N) in average (since you have to check which other node is connected to the node you want to delete).
void Graph::removeNode(string name) {
    //For all nodes in the nodemap... 
    for (auto x = nodemap.begin(); x != nodemap.end(); x++) {
        //Except itself..
        if (x->first != name) {
            //Bilaterally remove the connection to this node.
            removeEdge(x->first, name, true);
        }
    }

    //Delete the node.
    delete nodemap[name]; //The delete is to recover the memory that was dynamically allocated.
    nodemap[name] = nullptr; //Set the memory to null, just in case.
    nodemap.erase(name); //Restoring the memory on the nodemap.  
}

//Purpose: Helper function for breadth-first-search algorithm.
//Updates the queue with the unexplored connections of this node.
void Graph::updateQueue(GNode* cnode, queue<string> &q, unordered_map<string,bool> &explored) {
    //Special case: The node has no connections to explore.
    if (cnode->connections.size() == 0) {
        return;
    }

    //Add each unexplored connection to the queue.
    //For each connection at this node
    for (auto it = cnode->connections.begin(); it != cnode->connections.end(); it++) {
        //Add to the queue if not explored.
        if (!explored[it->first]) {
            q.push(it->first);
        }
    }
}

//Purpose: Search for a node from the start position. 
//Search current depth before moving to the next depth.
bool Graph::breadthFirstSearch(string root, string target) {
    //A queue for the algorithm to search in a level by level order.
    queue<string> q; 

    //A map that keeps track of which nodes have been explored.
    unordered_map<string,bool> explored; 
    
    //Create the explored vector.
    //For every key in the map.
    for (auto x = nodemap.begin(); x != nodemap.end(); x++) {
        //Make an entry in the explored vector where it starts as false as default.
        explored[x->first] = false;
    }

    //Begin the algorithm at the root. Place its name on the queue.
    q.push(root); 

    //Until you run out of unexplored nodes.
    while (q.size() != 0) {
        //Access the oldest element in the queue.
        GNode* cnode = nodemap[q.front()];

        //Print out which node you are currently searching.
        cout << cnode->name << " ";

        //If the name of the node matches the target...
        if (cnode->name == target) {
            //Return true and end the function.
            return true;
        }
        
        //Otherwise... 
        //Update the queue with the unexplored connections of this node.
        updateQueue(cnode, q, explored);

        //Update that this node has been explored.
        explored[cnode->name] = true;

        //Remove this node from the queue as you have already searched it and updated the queue with its unexplored connections.
        q.pop();
    }

    //You made it here because you did not find it.
    return false;
}

//Purpose: Recursive helper function for DepthFirstSearch.
//Input: 
//"cnode": The current graph node for the recursion.
//"target": Data of the node you want to find.
//"explored": Unordered-map that keeps track of which nodes are explored. Check if explored in O(1) average.
//"found": A boolean that keeps track on whether the target has been found.
void Graph::recursiveDBSearch(string cnode, string target, unordered_map<string,bool> &explored, bool &found) {
    //Recursive case: This node has unexplored connections.

    //Access the current node.
    GNode* n = nodemap[cnode];

    //Update the current node as explored.
    explored[cnode] = true;

    //Recursive call on each of its unexplored connections.
    for (auto x = n->connections.begin(); x !=n->connections.end(); x++) { 
        if (!explored[x->first]) {
            recursiveDBSearch(x->first, target, explored, found);
        }
    }

    //Print out which node you are searching.
    cout << cnode << " ";

    //You found the target.
    if (cnode == target) {
        found = true;
    }
    
    //Base case situation:
    //No unexplored connections left and you never found the target.
    return;

}

//Purpose: Depth-first-search the graph.
//O(N)
bool Graph::depthFirstSearch(string root, string target) {
    //Create a map that keeps track of what nodes have been explored.
    unordered_map<string,bool> explored;
    for (auto x = nodemap.begin(); x != nodemap.end(); x++) {
        //Make an entry in the explored vector where it starts as false as default.
        explored[x->first] = false;
    }
    
    //Call the helper function.
    bool found = false;
    recursiveDBSearch(root, target, explored, found);

    return found;
}