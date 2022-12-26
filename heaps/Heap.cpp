#include "Heap.h"

//Constructor
//Creates the vector (default size is 10) that holds the data .
//Assigns a minimum heap by default.
Heap::Heap (int default_size = 10, bool minimum_heap = true) {
    this->minimum_heap = minimum_heap;
    v.reserve(default_size);
}

//Purpose: Check if the heap is empty.
bool Heap::isEmpty() {
    return (v.size() == 0);
}

//Purpose: Print the heap, level by level.
void Heap::printHeap() {
    int i = 0;
    int level = 0;
    
    while (i < v.size()) {
        for (int x = 0; x < pow(2,level); x++) {
            if (i < v.size()) {
                cout << v[i] << " ";
            }
            i++;
        }
        
        cout << endl;
        level++;
    }
}

//Purpose: Compare integers depending on whether this is a minimum or maximum heap.
//If minimum heap: Return true if a <= b; false otherwise.
//If maximum heap: Return true if a >= b; false otherwise.
bool Heap::compare(int a, int b) {
    if (minimum_heap) {
        return a <= b;
    }
    else {
        return a > b;
    }
}

//Purpose: Recursively compares nodes to the parents until the nodes and parents have 
//the correct comparison (i.e. in a maximum heap, ensures the node is smaller than its parent).
void Heap::siftUp(int index) {
    //Base cases: 
    //No more parents to sift up OR the parent is already correctly positioned.
    if ( index <= 0 || compare(v[(index-1)/2],v[index]) ) {
        return;
    }

    //Recursive case: The parent and child are not correctly positioned.

    //Swap the values of the node and its parent.
    swap(v[index], v[(index-1)/2]);

    //Recursive call on the parent node.
    siftUp((index-1)/2);
}

//Purpose: Go to a specific index and recursively ensure that the node and the children have 
//the right comparison.
//Assumes that except for this specific index, the rest of the heap is properly constructed.
void Heap::heapify(int index) {
    //Base case #1: No more children elements to swap with.
    if ( (2*index + 1) >= v.size() ) {
        return;
    }

    //Base case #2: Only one more children to potentially swap with.
    //The queue is a complete binary tree, having a node with only one children 
    //signifies that child node is the end of the tree.
    if ( (2*index + 2) >=v.size() ) {
        //If the parent is not at the right position.
        if ( !compare(v[index],v[(2*index)+1]) ) {
            //Swap the values of the parent and child.
            swap(v[2*index+1],v[index]);     
        }
        return;
    }

    //Recursive case: Must compare to both children

    //Calculate the index of the child you may have to swap with.
    //(i.e. if it is a minimum heap -> get the index of the child with the lowest value).
    int swap_with_index = compare(v[2*index+1], v[2*index+2]) ? 2*index+1 : 2*index+2;

    //Check node and child have the correct comparison. 
    //If not...
    if ( !compare(v[index], v[swap_with_index]) ) {
        //Swap the values of the parent and appropriate child.
        swap(v[swap_with_index],v[index]);
        
        //Recursively heap from the node you swapped values with.
        heapify(swap_with_index);
    }
}

//Purpose: Insert a new element into the heap, respecting the heap (max or min) properties.
void Heap::insert(int data) {
    //Special case: The heap is empty.
    if (isEmpty()) {
        v.push_back(data);
        return;
    }

    //Insert at the end of the vector.
    v.push_back(data);

    //Sift up starting from the end of the vector.
    siftUp(v.size()-1);

}

//Purpose: Removes top element of the heap object.
void Heap::removeTop() {
    //Swap last element of the heap with the index you want to remove.
    swap(v[0],v[v.size()-1]);
    
    //Remove last element.
    v.pop_back();

    //Recursively heapify from the top.
    heapify(0);
}

//Purpose: Searches the heap for an appearance of the target and removes it.
void Heap::findAndRemove(int target) {
    for (unsigned int i = 0; i < v.size(); i++) {
        if (v[i] == target) {
            //Swap last element of the heap with the index you want to remove.
            swap(v[i],v[v.size()-1]);
    
            //Remove last element.
            v.pop_back();

            //Recursively heapify from this index
            heapify(i);

            //Only remove one of the instances.
            return;
        }
    }
}

//Purpose: Get the top value of the Heap.
int Heap::getTop() {
    //Error case: The heap is empty
    if (isEmpty()) {
        cout << "Error in getTop. There is nothing in the heap to retrieve. Returning nonsense." << endl;
        return 0;
    }

    //First element in vector is the top of the heap
    return v[0];
}