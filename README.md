# PedagogicalFunctionsInCPlusPlus  
A growing list of C++ libraries that contain my solutions to algorithms that were helpful for learning C++ and programming in general.  
Where appropriate I comment functions that were written with big help from different courses or web resources.  

Arrays  
Print arrays; reverse them.  
Search for an element: Linear method; binary method for sorted arrays.  
In an array of positive and negative numbers: Find the maximum sum of consecutive elements. 1) Brute Force 2) Prefix sum method 3) Kadane algorithm.  

Vectors  
Print vectors; find maximum/minimum of the elements; swap elements; reverse vectors.  
Sort by bubble algorithm; by optimized bubble algorithm; by insertion; by counting.  
Calculate the sum of two pairs closest to a target number; calculate how many elements you can pair together with a difference less than a target, etc... 

Vectors2D  
Print 2D vectors; print in spiral form; print as reverse wave.  
Check dimensionality; calculate the sum of a subportion of the 2D vector; search a sorted 2D vector.  
Create a 2D vector Pascal triangle.  
Get perimeter of a 2D vector; get specified inner loops; update 2D vectors with new perimeters/loops.  
Rotate a symmetric 2D vector by a variable amount.   
Compare cartesian points (as pair of integers); calculate distance between points; calculate distance to origin; compare distance to origin. Build a grid.  
Defense kingdom: Calculate the maximum undefended area of a variable-size chess board with a variable amount of rooks on it. 

Recursion  
Recursively move from x1 to x2; calculate factorial of n; calculate Fibonacci element n; recursively calculate power, brute and optimized.    
Print recursively from 0 to n; recursively search an array and find the elements.
Tiles problem (1xM tiles in an NxM board); Friend's party problem; Calculate number of different paths from corner to corner in an NxM grid.
Find possible binary permutations of size n that do not have consecutive 1s.  
Merge sort; quick sort.

Linked-Lists  
Custom Node class.  
Custom Linked-List class. Class Methods: Insert element in O(1). Remove the head or tail in O(1). Search for an element. Insert an element at a specific position. Delete an element at a specific position. Get the kth last element by iterating through only once. Reverse the linked-list.  
Custom Stack Class, implemented as a linked list. Class Methods: Push in O(1), remove top element O(1). Place an element in the bottom of the stack.  
Custom Queue Class, implemented as a linked list. Push and pop in O(1). 

Binary-Trees  
Custom Binary-Tree-Node class.  
Custom Binary-Tree class implemented as linked lists of binary-tree nodes. Class Methods: Build the tree using an input vector (pre-order arranged). Print an existing tree in either: pre-order, in-order, post-order, or level-order. Search if an element is inside the tree. Read an existing tree and save elements into a vector. Search if an element is inside the tree (breadth-first search or depth-first search); count how many instances an element is found. Rotate (left or right) the root or a specific element.  
Custom Binary-Search Tree class inheriting from the Binary-Tree Class. Polymorphism in building the binary search tree using an input vector. Insert a new element into the binary search tree by keeping the node's relationships valid. Find max, min values. Remove a node, whether it is a leaf, has a single child, or has two children. 

Heaps  
Custom Heap class implemented as a vector conceptualized as a complete binary tree. Class Methods: Printing the heap, level by level. Sift up; sift down (heapify); insert a new element; remove top element; find and remove specific element (closest to the top).  

Hash Tables  
Custom Hash class: Custom hash function, hash table, and linked-lists for collision handling. Rehashing function when the table exceeds a custom load factor. 
Class Methods:  Search a key and return value in O(1)-average; insert a new element in O(1); erase an element in O(1)-average; overload the [] operator.  

Tries  
Custom Trie class implemented as a tree of custom nodes. Methods: Search in O(key-length); insert a new word O(key-length).  
