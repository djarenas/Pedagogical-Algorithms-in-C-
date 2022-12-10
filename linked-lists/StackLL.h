#ifndef STACKLL_H
#define STACKLL_H

#include "Node.h"

//Class: StackLL. A stack implemented as linked lists of nodes<typename T>.
template <typename T>
class StackLL {
    Node<T>* top; //A pointer that keeps track of the top node. All nodes can be found starting from here.

  public: 

    //Constructor.
    StackLL() {
        top = nullptr;
    }

    //Destructor
    ~StackLL() {
        if (top != nullptr) {
            //Ask compiler to destroy everything in this stack.
            delete top; //The Node Class destructor will recursively delete everything.
            top = nullptr;
        }
    }
    
    //METHODS

    //Purpose: Print the StackLL object.
    void printStackLL() {
        //Special case: The StackLL object is empty.
        if (top == nullptr) {
            cout << "Nothing to print on this stack" << endl;
            return;
        }
        
        Node<T>* cnode = top; //Temporary node starting from the top.     
        while (cnode != nullptr) {      
            cout << cnode->data << "->";
            cnode = cnode->next;
        }

        cout << endl;
    }
    
    //Purpose: Push data to the top of the StackLL object. O(1).
    void push(T data) {
        //Create dynamic memory for new node. 
        Node<T>* n = new Node<T>(data); //Dynamically-allocated memory is deleted by the Node class destructor.
        
        //Make this new node point to the current top.
        n->next = top;

        //Update this new node as the new top. 
        top = n;
    }

    //Purpose: Check if the StackLL object is empty.
    bool isEmpty() {
        return top==nullptr;
    }

    //Purpose: Return the top element. Does not modify the StackLL object. O(1).
    T getTop() {
        return top->data;
    }

    //Purpose: Delete the top element of the StackLL object. O(1).
    void pop() {
        //Error case: There are no elements to pop.
        if ( isEmpty() ) {
            cout << "Error in pop. This stack is empty. Terminating." << endl;
            return; 
        }

        //Keep track of node below the top.
        Node<T>* below = top->next;

        //Make the current top point to null so that you don't recursively delete everything.
        top->next = nullptr;

        delete top;

        //Update the below element as the new top.
        top = below;
    }

    //Purpose: Place an element at the bottom of the stack. O(N).
    void placeAtBottom (T data) {

        //Special case: The stack is empty; just use push.
        if ( isEmpty() ) {
            push(data);
            return;
        }
        
        //A temporary "current node" for iterating to the bottom of the stack. Start at the top.
        Node<T>* cnode = top;

        //Iterate from the top to the bottom.
        while (cnode->next != nullptr) {
            cnode = cnode->next;
        }

        //You are now at the bottom element.
        //Make this element point to a new node.
        Node<T>* n = new Node<T>(data); 
        cnode->next = n;
        n->next = nullptr; //New node at the bottom should point to null
    }
};

#endif
