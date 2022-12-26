#ifndef HEAP_H
#define HEAP_H

#include <cmath>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::swap;
using std::vector;

//Purpose: A Heap class implemented as a vector conceptualizing a complete binary tree.
//Can be initialized as either a max or min heap.
class Heap {
private:
    
    vector<int> v; //A vector of integers representing a complete binary tree.
    bool minimum_heap; //A boolean to denote whether the instantiation is a minumum (true) or maximum (false) heap.

public:

    //Constructor

    Heap (int default_size, bool minimum_heap);

    //METHODS
    
    bool isEmpty();
    void printHeap();
    bool compare(int a, int b);
    void siftUp(int index);
    void heapify(int index);
    void insert(int data);
    void removeTop();
    void findAndRemove(int target);
    int getTop();
};

#endif
