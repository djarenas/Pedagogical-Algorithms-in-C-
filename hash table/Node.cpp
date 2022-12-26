#include "Node.h"

//Constructor
template <typename T>
Node<T>::Node(string key, T data) {
    this->data = data;
    this->key = key;
    next = nullptr;
}

//Destructor
//Recursively deletes nodes chained by the linked-lists.
template <typename T>
Node<T>::~Node() {
    cout << "Currently deleting: " << key << endl; 
    if (next != nullptr) {
        delete next; 
    }
}