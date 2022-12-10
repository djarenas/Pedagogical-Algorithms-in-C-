#ifndef LINKLIST_H
#define LINKLIST_H

#include "Node.h"

//List class: Stores a pointer to a head node and a tail node. 
//Node's architecture is such that each node holds its own data and the address to the next node.
template <typename T>
class LinkList {
    Node<T> *head; //A pointer to the first element in the linked list.
    Node<T> *tail; //A pointer to the last element.

  public:

    //Constructor.
    //The list at first contains no valid nodes.
    LinkList() {
        head = nullptr; 
        tail = nullptr; 
    }

    //Destructor.
    //Must delete dynamically-allocated memory.;
    ~LinkList() {
        if (head != nullptr) {
            //Ask compiler to destroy everything pointed to by head.
            //The node destructor will recursively delete everything linked to the head.
            delete head; 

            //Update head to be empty.
            head = nullptr;
        }
    }
    
    //METHODS

    //Purpose: Print the Linked List. Starts from the head.
    void printLinkList() {
        //Special case: The linked list is empty.
        if (head == nullptr) {
            cout << "The linked list is empty." << endl;
            return;
        }
        
        //A temporary "current node" pointer to iterate through the linkedlist.
        Node<T>* cnode = head; 
        
        while (cnode != nullptr) {
            cout << cnode->data << "->";
            cnode = cnode->next; //Move to next node.
        }
        
        cout << endl;
    }

    //Purpose: Add a new element as the head of the Linked List.
    void push_front(T data) {
        //Special case: The list is currently empty -> This element becomes the head and tail.
        if (head == nullptr) {
            //Create a dynamically allocated node.
            //Note: This dynamically-allocated memory is removed by the Node Class destructor. 
            Node<T> *n = new Node<T>(data); 

            //Since this new node is the only element, make the head and tail point to it.
            head = tail = n;

            return;
        }
        
        //General cases: The linked list is not empty.

        //Create a dynamically allocated node.
        Node<T> *n = new Node<T>(data);
            
        //Make the next value of this new node point to the current head node.
        n->next = head; 

        //Update his new node as the new head.
        head = n;
    }

    //Purpose: Add a new element as the tail.
    void push_back(T data) {
        //Special case: The list is currently empty -> This element becomes the head and tail.
        if (head == nullptr) {
            push_front(data);
            return;
        }
        
        //General cases: The linked list is not empty.

        //Create a dynamically allocated node. 
        Node<T> *n = new Node<T>(data); 

        //Make the current tail point to this new node.
        tail->next = n;

        //Update this new node as the new tail.
        tail = n;        
    }

    //Purpose: Insert a new element at a specified location.
    void insert(T data, int position) {
        //Special case: The desired position is zero.
        if (position == 0) {
            push_front(data);
            return;
        }
        
        //Temporary node ("current node") to iterate through the Linked List. 
        Node<T>* cnode = head; 

        //Move from beginning to position.
        for (int i = 1; i < position; i++) {
            cnode = cnode->next;
            //Check that you haven't reached exceeded the end of the linked list or an error in the linking between nodes.
            if (cnode == nullptr) {
                cout << "Error in insert method for LinkList. Not a valid position. Terminating.";
                return;
            }
        }

        //You are now at the correct position node.
        //Create a new dynamically-allocated node.
        Node<T> *n = new Node<T>(data);

        //Give the new node the same next as current node.
        n->next = cnode->next;

        //Now make the current node have the new node as next.
        cnode->next = n; 
    }

    //Purpose: Delete first element of a Linked List object.
    void pop_front() {

        //If there are no elements in the linked list.
        if (head == nullptr) {
            return;
        }

        //Make a temporary node where the current head is. So you know where to come back to.
        Node<T>* temp = head;

        //Make the new head the next link after the old head.
        head = head->next;

        //Make the old head point to a null pointer.
        //This prevents the Node destructor from recursively deleting the rest of the list.
        temp-> next = nullptr;

        //Delete the old head. Compiler will call the destructor for Node.
        delete temp; 
    }

    //Purpose: Delete last element of linked list.
    void pop_back() {
        
        //If there are no elements in the linked list.
        if (head == nullptr) {
            return;
        }

        //If there is only element in the linked list.
        if (head->next == nullptr) {
            pop_front();
            return;
        }

        //Temporary node ("current node") to iterate through the Linked List. 
        Node<T>* cnode = head; 
        
        //Linearly search until the penultimate element.
        while (cnode->next->next != nullptr) {
            cnode =cnode->next;
        }
        
        //You are now at the penultimate element.
        //Delete the old tail.
        delete cnode->next;
        
        //Set the next of this current node as null.
        cnode->next = nullptr;     
    }

    //Purpose: Remove specific element of the linked list.
    void removeSpecificIndex(int position) {
        //No list, nothing to remove,
        if (head == nullptr) {
            return;
        }

        //If position zero, just pop front.
        if (position == 0) {
            pop_front();
            return;
        }

        //Move from beginning to the element previous to the position you want
        Node<T>* cnode = head; 
        for (int i = 1; i < position; i++) {
            cnode = cnode->next;
            if (cnode->next == nullptr) {
                cout << "Error in removeSpecificIndex. " << position << " is not a valid position" << endl;
                return;
            }
        }
            
        //Make a temporary position of what you will delete.
        Node<T>* temp = cnode->next;

        //Make this position skip the next one.
        cnode->next = cnode->next->next;

        //Make the next of what you will delete a nullpointer to avoid recursive calls.
        temp->next = nullptr; 
        
        delete temp;
    }

    //Purpose: Return the kth last element.
    //Last element is k = 1; penultimate is k = 2;....
    int getKthLastElement(int k) {
        
        if (k < 1) {
            cout << "Error in getKthLastElement. K must be equal or more than one." << endl;
            return 0;
        }

        //Starting from the head: Move Kth steps.
        Node<T>* cnode = head;
        for (int i = 0; i < k; i++) {
            //Check that more steps are actually possible.
            if (cnode->next == nullptr) {
                cout << "Error in getKthLastElement. The linked list is not long enough to get a kth last element." << endl;
                return 0;
            }

            cnode = cnode->next;
        }

        //Save a temporary node at the head. This now lags kth steps behind the current node "cnode".
        Node<T>* temp = head;

        //Now move both until cnode hits the end.
        while (cnode != nullptr) {
            temp = temp->next;
            cnode = cnode->next;
        }

        return (temp->data);
    }

    //Purpose: Search the linked list for a key. 
    //Returns the earliest index where found. Returns -1 if not found.
    int linearSearch(T key) {
        //Declare a current node and start at the head.
        Node<T>* cnode = head;

        int i = 0; //A counter for keeping track of how many elements you have searched
        
        //Move accross the linked list until you hit a null pointer.
        while (cnode != nullptr) {
            if (cnode->data == key) {
                return i;
            }

            //Move to next node in the linked list. Update the counter.
            cnode = cnode->next;
            i++;
        }
        
        //You are here because you hit a null pointer and didn't find the element.
        return -1;
    }


    //Purpose: Reverse a linked list.
    void reverseLinkedList() {
        //Do nothing if there are no elements or only one element.
        if (head == nullptr || head->next == nullptr) {
            return;
        }
        
        //Declare a current node at the element next to head. 
        //Keep track of its left and right.
        Node<T>* temp_left = head; //A node that keeps track of the previous element.
        Node<T>* cnode = head->next; //Current element.
        Node<T>* temp_right = cnode->next; //Keep track of next element

        //Make current head point to nullptr.
        //Call it the tail now.
        head->next = nullptr;
        tail = head;

        //Begin at head but reverse the element next to it.
        while (cnode->next != nullptr) {
            //Make the current node now point to the left.
            cnode->next = temp_left;
            
            //Prepare the move to the next iteration.
            temp_left = cnode; //Move left element: Make the value the same as current
            cnode = temp_right; //Move current element.
            temp_right = temp_right->next;
        }
        
        //For last element
        cnode->next = temp_left;
        head = cnode;
    }
};

#endif
