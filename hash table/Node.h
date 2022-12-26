#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

//Forward declarations

template <typename T>
class Hashtable;

//Purpose: Class for the nodes to be implemented in the architecture of the Class Hashtable.
//The key will always be a string; the data will be of variable type.
//Each node will have an address for a possible next node (Separate chaining for collision handling).
//Explicit instantiations for int, float, double, string, bool.
template <typename T>
class Node {

    string key;
    T data;
    Node* next;

private:

    //Constructor, destructor, 

    Node(string key, T data);
    ~Node();

    friend class Hashtable<T>;
};

//EXPLICIT INSTANTIATIONS
template class Node<int>;
template class Node<float>;
template class Node<double>;
template class Node<string>;
template class Node<bool>;

#endif
