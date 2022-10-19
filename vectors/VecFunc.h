#include <algorithm>
#include <bitset>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;
using std::endl;

namespace VecFunc {

    //Purpose: Print integer vector. Passed by reference.
    void printVect (vector<int> &A);

    // //Purpose: Print string vector. Passed by reference.
    void printVect (vector<string> &A);

    //Purpose: Find maximum element of vector of integers.
    int findVectorMax(vector<int> &A);

    // //Purpose: Find minimum element of vector of integers.
    int findVectorMin(vector<int> &A);

    //Purpose: Find minimum element of vector of integers.
    int findVectorMin(vector<int> &A);

    //Purpose: Takes a vector of integers and swaps its x and y elements.
    void swapElem (vector<int> &A, int x, int y);

    //Purpose: Takes a vector of integers and reverses it. Original vector modified in place.
    void reverseVector (vector<int> &A);

    //Purpose: Vector of integers --> Sorted vector.
    //Bubble algorithm. O(n^2).
    void sortbyBubble (vector<int> &A);

    //Purpose: Vector of integers --> Sorted vector.
    //Bubble algorithm. O(n^2). Best case O(n) if already sorted.
    void sortByOptimizedBubble(vector<int> &A);

    //Purpose: Vector of integers --> Sorted vector.
    //Sorty by Insertion. ~O(n^2).
    void sortByInsert(vector<int> &A);

    //Purpose: Vector of integers --> sorted vectors. Histogram method.
    //O(n + k). k is length of the histogram vector (max - min + 1).
    void sortbyCounting(vector<int> &A);

    //Purpose: Given a vector with N integers, find the possible number of pairs
    //of elements for which the difference is equal or less than x. No element can pair more than once.
    //This problem is presented as the Chopsticks problem in Prateek Narang's Data Structures & 
    //algorithms for C++.
    int calcPairDifferencesLessThanX (vector<int> A, int x);

    //Purpose: Vector of integers and a target integer x -> Find the pair of elements 
    //whose sum is closest to x. 
    pair<int,int> findClosestSumPair(vector<int> vect, int x);

};
