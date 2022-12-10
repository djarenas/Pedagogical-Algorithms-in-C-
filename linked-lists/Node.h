//Header guards
#ifndef NODE_H
#define NODE_H

#include <iostream>

using std::cout;
using std::endl;
using std::string;

//Forward declarations.
template <typename T>
class LinkList;
template <typename T>
class StackLL;
template <typename T>
class QueueLL;

//Class: Node. Stores data of typename T. Stores a pointer to next node.
template <typename T>
class Node {
    T data;
    Node<T>* next; //Declare the pointer that keeps track of the next element.

  public:
    //Constructor.
    Node(T data) {
        this->data = data;
        next = nullptr; 
    }

    //Destructor. Needs to recursively delete dynamically allocated data.
    ~Node() {
        cout << "Destructor currently operating on Node: " << data << " at: " << &data << "." << endl;
        //If there are elements after this node, delete the next one too.
        if (next != nullptr) {
            delete next; //Recursively calls this destructor.
        }
    }

    friend class StackLL<T>;
    friend class QueueLL<T>;
    friend class LinkList<T>;
};

#endif
