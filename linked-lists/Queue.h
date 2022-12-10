#ifndef QUEUELL_H
#define QUEUELL_H

#include "Node.h"

//Class QueueLL: Implemented as a linked list of nodes that keeps track of the front and rear.
template <typename T>
class QueueLL {
    Node<T>* front;
    Node<T>* rear;

  public:
    
    //Constructor.
    QueueLL() {
        front = nullptr;
        rear = nullptr;
    }

    //Destructor.
    ~QueueLL() {
        if (front != nullptr) {
            delete front; //The node destructor recursively deletes all nodes after this front node.
        }
    }

    //METHODS

    //Purpose: Add element to the queue. Its added to the rear.
    void push(T data) {

        //Create new node. Dynamically-allocated. Designed to be destroyed by the Node destructor.
        Node<T>* n = new Node<T>(data);

        //Special case: The QueueLL object is empt and this new node becomes the front and rear.
        if (front == nullptr) {
            front = n;
            rear = n;
            return;
        }

        //General case: The queue was not empty.
        
        //Have the current rear point to the new node.
        rear->next = n;

        //Update the new node as the new rear.
        rear = n;
    }

    //Purpose: Pop an element out. First in first out.
    void pop() {
        //Error case: Nothing on the queue to pop.
        if (front == nullptr) {
            cout << "Error in pop. Nothing to remove on this QueueLL object. Terminating." << endl;
            return;
        }

        //Make a temporary copy of the front element
        Node<T>* temp = front;

        //Make the next element the new front.
        front = front-> next;

        //The temporary node holds the location of the old front. 
        //Make it point to null so that the Node destructor does not recursively delete the rest of the nodes.
        temp->next = nullptr;
        
        delete temp;
    }

    //Purpose: Print the Queue Link-List.
    void printQueueLL() {
        //Special case: Nothing on the queue to print
        if (front == nullptr) {
            cout << "Nothing to print on this QueueLL object. Terminating." << endl;
            return;
        }

        //Iterate through the queue.
        Node<T>* cnode = front;
        while (cnode != nullptr) {
            cout << cnode->data << "->";
            cnode = cnode->next;
        }
        cout << endl;
    }
};

#endif
