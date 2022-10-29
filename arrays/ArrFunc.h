#include <iostream>

using std::cout;
using std::endl;

namespace ArrFunc {

    //Purpose: Print to console an array.
    //Input: Array and size of array (size is needed for C++).
    void printArray(int arr[], int n);

    //Purpose: Reverse an integer array.
    void reverseArray(int arr[], int n);

    //Purpose: Return the sum of the array.
    int sumArray(int arr[], int n);

    //Purpose: Brute linear search an array for a target integer.
    //Returns the first element of the array when found. Returns -1 if not found.
    int searchLinear(int arr[], int n, int target);

    //Purpose: Binary search a sorted array for a target integer.
    //Returns the first element of the array when found. Returns -1 if not found.
    int searchBinary(int arr[], int n, int target);

    //Purpose: Array of (+) and (-) integers -> Find maximum possible sum of consecutive elements.
    //Example: {-6,7,8,-5,20,-35,15} -> 30
    //Brute force. O(n^3).
    int findMaxFromConsecutiveBrutely(int arr[], int n);

    //Purpose: Array of (+) and (-) integers -> Find maximum possible sum of consecutive elements.
    //Example: {-6,7,8,-5,20,-35,15} -> 30
    //Prefix method. O(n^2).
    int findMaxFromConsecutiveByPrefixSum(int arr[], int n);

    //Purpose: Array of (+) and (-) integers -> Find maximum possible sum of consecutive elements.
    //Example: {-6,7,8,-5,20,-35,15} -> 30
    //Prefix method. O(n^2).
    int doKadaneAlgorithm(int arr[], int n);

}