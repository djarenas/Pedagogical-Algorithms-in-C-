#include "VecFunc.h"

//Purpose: Print integer vector. Passed by reference.
void VecFunc::printVect (vector<int> &A) {
    vector<int>::iterator it;
    for (it = A.begin(); it < A.end(); it++){
        cout << *(it) << "\t";
    }
    cout << endl;
}

//Purpose: Print string vector. Passed by reference.
void VecFunc::printVect (vector<string> &A) {
    vector<string>::iterator it;
    for (it = A.begin(); it < A.end(); it++){
        cout << *(it) << "\t";
    }
    cout << endl;
}

//Purpose: Find maximum element of vector of integers.
int VecFunc::findVectorMax(vector<int> &A) {
    int maxe = A[0];
    for (vector<int>::iterator it = A.begin(); it < A.end(); it++) {
        maxe = *(it) > maxe ? *(it) : maxe;
    }
    return maxe;
}

//Purpose: Find minimum element of vector of integers.
int VecFunc::findVectorMin(vector<int> &A) {
    int mini = A[0];
    for (vector<int>::iterator it = A.begin(); it < A.end(); it++) {
        mini = *(it) < mini ? *(it) : mini;
    }
    return mini;
}

//Purpose: Takes a vector of integers and swaps its x and y elements.
void VecFunc::swapElem (vector<int> &A, int x, int y) {
    int temp = A[x];
    A[x] = A[y];
    A[y] = temp;
}

//Purpose: Takes a vector of integers and reverses it. Original vector modified in place.
void VecFunc::reverseVector (vector<int> &A) {
    int n = A.size();
    for (int i = 0; i < n/2; i++ ){
        int temp = A[n - 1 - i];
        A[n -1-i] = A[i];
        A[i] = temp;
    }
}

//Purpose: Vector of integers --> Sorted vector.
//Bubble algorithm. O(n^2).
void VecFunc::sortbyBubble (vector<int> &A) {
    int n = A.size();
    //For each ith element
    for (int i = 0; i < n - 1; i++){
        //Swap from one to the next until the highest is at the end of the array
        for (int j = 0; j < n - 1 - i; j++){
            if (A[j+1] < A[j]){
                swapElem(A, j, j+1);
            }
        }
    }
}

//Purpose: Vector of integers --> Sorted vector.
//Bubble algorithm. O(n^2). Best case O(n) if already sorted.
void VecFunc::sortByOptimizedBubble(vector<int> &A) { 
    int n = A.size();
    //For each ith element
    for (int i = 0; i < n - 1; i++){ 
        //VecFunc::printVect(A); A good place to print the vector to see how the algorithm is working 

        //Assume that things after the ith element are indeed sorted
        bool unsorted = false;

        //Keep swapping higher elements to the right until they are at the end of the vector
        for (int j = 0; j < n - 1 - i; j++){
            if (A[j+1] < A[j]){
                VecFunc::swapElem(A, j, j+1);
                //If you have to swap, then update that things were not sorted.
                unsorted = true;
            }
        }

        //If you never had to swap, then things are sorted after the ith element and you can break.
        if (unsorted == false){
            cout << "Already in order, breaking" << endl;
            return;
        }
    }
}

//Purpose: Vector of integers --> Sorted vector.
//Sorty by Insertion. ~O(n^2).
void VecFunc::sortByInsert(vector<int> &A) {
    int n = A.size();
    int i = 1; //Delineates between sorted and not-sorted.
    
    while (i < n){
        int temp = A[i]; //Keep track of this element. The first in the non-sorted.

        //Begin from the last element in the sorted.
        int j = i -1;
        while (A[j] > temp & j >= 0) {
            A[j+1] = A[j]; //If this element is bigger than temp, then copy it to the next element.
            j--; //Move left 
        }
       
        //The leftest element that was not changed, put back the temp here. 
        A[j+1] = temp;
        
        //Move the sorted delineator to the right
        i++;
    }
}

//Purpose: Vector of integers --> sorted vectors. Histogram method.
//O(n + k). k is length of the histogram vector (max - min + 1).
void VecFunc::sortbyCounting(vector<int> &A) {
    int n = A.size();

    //Build the histogram vector with default values of zero.
    //Start the histogram at the minimum value of the input vector. 
    //It ends at the maximum of the input vector.
    int maxe = VecFunc::findVectorMax(A);
    int mini = VecFunc::findVectorMin(A);
    int hn = (maxe-mini+1);
    vector<int> hvector(hn,0); 

    //Find the frequencies of the histogram vector.
    //Remember the first element of the histogram corresponds to the minimum in the input vector.
    //Therefore hvector[0] is the counts of the minimum value. hvector[hn] the counts of the maximum.
    for (int i = 0; i < n; i++){
        //If first element of input vector is 2 => update the histogram of 2 - minimum
        hvector[A[i]-mini] = hvector[A[i]-mini] + 1;
    }

    //Use the histogram to resort the array
    int x = 0; //Keep track of element in being-sorted array
    
    //For each element in the histogram
    for (unsigned j = 0; j < hvector.size(); j++){
        //Add to the input vector as many of the element as there are counts
        while(hvector[j] != 0){
            A[x] = j + mini; //The first element of the histogram corresponded to the minimum.
            hvector[j]--; //Decrease the counts by 1
            x++; //Move to the next element of the sorted vector
        }
    }
}

//Purpose: Given a vector with N integers, find the possible number of pairs
//of elements for which the difference is equal or less than x. No element can pair more than once.
//This problem is presented as the Chopsticks problem in Prateek Narang's Data Structures & 
//algorithms for C++.
int VecFunc::calcPairDifferencesLessThanX (vector<int> A, int x) {
    //This algorithm requires the vector to be sorted.
    sort(A.begin(), A.end());
    
    int n = A.size();
    int pairs = 0; //Return variable
    
    int i = 1;
    while (i < n){
        //If you find two adjacent elements for which the difference is less than x.
        if (A[i] - A[i-1] <= x){
            //Add one more pair to the result.
            pairs++;   
            //Move two elements since an element cannot pair twice.
            i = i + 2;
        }
        //If not, go to next element.
        else {
            i++;
        }
    }
    return  pairs;
}

//Purpose: In a vector of integers, find the pair of elements whose sum is closest to x.
pair<int,int> VecFunc::findClosestSumPair(vector<int> vect, int x) {

    int n = vect.size();

    //Sort the vector so that you know you can start at the two ends and then move them appropriately.
    sort(vect.begin(), vect.end());

    //Keeping track of the minimum of delta (the difference between the sum and x)
    int mindelta; 
    //and the elements where you found it. 
    int l_ans = 0;
    int r_ans = n - 1;

    //Begin the search at the two ends of the array: left and right.
    int l = 0; //Leftmost element, will only be moved right (since the vector was sorted earlier)
    int r = n-1; //Rightmost element, will only be moved left.
    mindelta = abs((vect[r]+vect[l])-x); //Calculate delta and first assume the minimum to be at the sum of the ends.

    //Allow L and R elements to move in their respective directions 
    //right up until they are next to each other (l < r).
    while (l < r) {
        //Calculate the difference between the two elements sum and the target.
        int delta = (vect[r]+vect[l])-x; 
        
        //If the sum is exactly the target, return the two elements.
        if (delta == 0) {
            return std::make_pair(vect[l], vect[r]);
        }
        
        //Update the minimum delta if you got a smaller delta in this iteration.    
        if (abs(delta) < mindelta) {
            l_ans = l;
            r_ans = r;
            mindelta = abs(delta);
        } 

        //To go to next iteration
        //If sum is high, move the leftmost to the right. If too low, rightmost to the left. 
        if (delta > 0) {
            r--;
        }
        if (delta < 0) {
            l++;
        }
    }
    //l_ans and r_ans were keeping track of where the mindelta was found
    return std::make_pair(vect[l_ans],vect[r_ans]);
}
