#include "ArrFunc.h"

//Purpose: Print to console an array.
//Input: Array and size of array (size is needed for C++).
void ArrFunc::printArray(int arr[], int n) {
    for (int i = 0; i < n; i++){
        cout << arr[i] << "\t";
    }
    cout << endl;
}

//Purpose: Return the sum of the array.
int ArrFunc::sumArray(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum = arr[i] + sum;
    }
    return sum;
}

//Purpose: Reverse an integer array.
void ArrFunc::reverseArray(int arr[], int n) { 
    for (int i = 0; i < n/2; i++){
        int temp = arr[n-1-i];
        arr[n-1-i] = arr[i];
        arr[i] = temp;
    }  
}

//Purpose: Brute linear search an array for a target integer.
//Returns the first element of the array when found. Returns -1 if not found.
int ArrFunc::searchLinear(int arr[], int n, int target) {
    int i = 0;
    int found = -1; //Return variable. Default is not found (-1).
    
    while (i < n & found == -1) {
        if (arr[i] == target) {
            found = i;
        }
        i++;
    }
    return found;
}

//Purpose: Binary search a sorted array for a target integer.
//Returns the index of the array when found. Returns -1 if not found.
int ArrFunc::searchBinary(int arr[], int n, int target){
    int s = 0; //The updating start-point.
    int e = n - 1; //The updating end-point.
    
    //Stop when the start-point is at or past the end-point.
    while (s<=e){
        int mp = (s+e)/2; //Current middle point.
        cout << arr[mp] << endl;
        //Evaluate at middle point. Return if found there.
        if (arr[mp] == target){
            return mp;
        }

        //If target is larger than middle element, move the start-point next to middle.
        if (target > arr[mp]){
            s = mp + 1;
        }
        //If target is smaller than middle element, move the end to the middle's left.
        if (target < arr[mp]){
            e = mp - 1;
        }
    }
    //You have searched everything, nothing found, return -1
    return -1;
}

//Purpose: Array of (+) and (-) integers -> Find maximum possible sum of consecutive elements.
//Example: {-6,7,8,-5,20,-35,15} -> 30
//Brute force. O(n^3).
int ArrFunc::findMaxFromConsecutiveBrutely(int arr[], int n) {
    int max = arr[0];
    
    //Sample all possible beginnings
    for (int s = 0; s < n; s++) {

        
        //Sample all possible endings
        for (int e = n; e > s; e--) {
            
            int r = 0;

            //Sum from beginning to end
            for(int i = s; i < e; i++) {
                r+= arr[i];
                //Update the max if appropriate
                max = r > max ? r : max;
            }
        }
    }
    return max;
}

//Purpose: Array of (+) and (-) integers -> Find maximum possible sum of consecutive elements.
//Example: {-6,7,8,-5,20,-35,15} -> 30
//Prefix method. O(n^2).
int ArrFunc::findMaxFromConsecutiveByPrefixSum(int arr[], int n) {

    int maxs; //Return variable

    //Initizalize prefix sum array with the first element of input array
    int psum_arr[n] = {arr[0]}; 
    //ith element in prefix sum array is the sum of the original array up until that point
    //Example: input {2,4,-2} --> {2,6,4};
    for (int i = 1; i < n; i++){
        psum_arr[i] = psum_arr[i-1]+arr[i];
    }

    //Set the first maximum sum as the simple sum of the whole array.
    maxs = psum_arr[n-1]; 

    //Explore different samplings of the prefix sum array: From ith to jth.
    int expl = 0;
    
    //Explore different endings (jth)
    for (int j = n-1; j >= 0; j--) {
        
        //Explore different starting points
        for (int i = 0; i < j; i++) {
            
            //If you start at i, you forfeit the sum before that i - 1.
            if (i != 0) {
                expl = psum_arr[j] - psum_arr[i-1]; //prefix sum would be zero before i = 0 anyway. 
            }

            //Update the maximum if so.
            maxs = std::max(expl, maxs);
        }     
    }
    return maxs;
}

//Purpose: Array of (+) and (-) integers -> Find maximum possible sum of consecutive elements.
//Example: {-6,7,8,-5,20,-35,15} -> 30
//Prefix method. O(n^2).
int ArrFunc::doKadaneAlgorithm(int arr[], int n){
    
    int maxs = 0; //Return variable. Current max.

    int c = 0; //Current sum.    
    //Linear loop over the array
    for (int i = 0; i < n; i++){
        //Add this element to the current sum.
        //But if the sum becomes negative change to zero.
        //The maximum is updated if the new sum is not zero.
        c = c + arr[i]; 
        c = c < 0 ? 0 : c; 
        maxs = c == 0 ? maxs : std::max(c, maxs); 
    }
    return maxs;
}


