#include "recursion.h"

void printVect (vector<string> &A) {
    vector<string>::iterator it;
    for (it = A.begin(); it < A.end(); it++){
        cout << *(it) << "\t";
    }
    cout << endl;
}

void printVect (vector<int> &A) {
    vector<int>::iterator it;
    for (it = A.begin(); it < A.end(); it++){
        cout << *(it) << " ";
    }
    cout << endl;
}

//Purpose: Recursively move position x1 to position x2.
void goHome(int x1, int x2) {
    //Base case: You made it to x2.
    if (x1 == x2) {
        cout << "You are home: " << x1 << endl;
        return;
    }

    //Recursion case: Keep moving.

    if (x1 < x2) {
        cout << "You are not home: " << x1 << endl;
        return goHome(x1 + 1, x2);
    }
    else {
        cout << "You are not home: " << x1 << endl;
        return goHome(x1 - 1, x2);
    }
}

//Purpose: Recursively calculate n factorial.
//Will return 1 for incorrect negative number inputs. //Max n is 20.
unsigned long long calcFactorial(int n) {
    //Special case: n is too large.
    if (n > 20) {
        cout << "n is too large. Terminating." << endl;
        return 0;
    }
    
    //Base cases 0! = 1. 1! = 1. Ignore negative numbers and return 1.
    if (n <= 1) {
        return 1;
    }
    else {
        return (n * calcFactorial(n-1));
    }
}

//Purpose: Recursively calculate an element in the Fibonacci sequence.
//Assume that f(0) = 0; f(1) = 1. Returns zero for improper negative number inputs.
int calcFibonacci(int n) {
    //Special case: A negative number was input.
    if (n < 0) {
        cout << "Incorrect input in calcFibonacci. Number must be zero or positive. Terminating." << endl;
        return -1;
    }
    
    //Base cases
    if (n == 0 || n == 1) {
        return n;
    }

    //Recursive case:
    //Problems that can be divided into the subproblem: n > 1
    else {
        return (calcFibonacci(n-1) + calcFibonacci (n -2));
    }
}

//Purpose: Recursively calculate x raised to a positive power p.
//O(p) in time and memory.
long long calcPowerRecursively(int x, int p) {
    //Error case: p is negative.
    if (p < 0) {
        cout << "Error in calcPowerRecursively. Power must be positive for this function." << endl;
        return 0;
    }
    
    //Base case: p = 0.
    if (p == 0) {
        return 1;
    }
    
    //Recursive case
    return (x * calcPowerRecursively(x, p-1));
}

//Purpose: Optimized recursion to calculate x raised to the p.
//O(log p) in time and memory.
long long calcPowerOptimized(int x, int p) {
    //Error case: p is negative.
    if (p < 0) {
        cout << "Error in calcPowerRecursively. Power must be positive for this function." << endl;
        return 0;
    }

    //Base case: p = 0
    if (p == 1) {
        return x;
    }
    
    //Recursive case

    //If p is odd: f(x,p) = x*f(p/2)*f(p/2)
    if (p%2 == 1) {
        long long temp = calcPowerOptimized(x,p/2);
        return x*temp*temp;
    }

    //If p is even: f(x,p) = f(p/2)*f(p/2)
    long long temp = calcPowerOptimized(x,p/2);
    return temp * temp;
}

//Purpose: Recursively prints from zero to N or N to zero.
//The function is called N, N-1, N-2,...
//Input: 1) Integer n 2) A boolean on whether you want printing to be increasing (true) or decreasing (false).
//A great example of taking advantadge of the Stack Call concept.
void printRecursively(int n, bool increasing) {
    //Base case: n = 0
    if (n == 0) {
        return;
    }

    //Recursion case: Go to smaller subproblem: n - 1

    //Print towards base case if you want it to be decreasing
    if (!increasing) {
        cout << n << " ";
        cout << endl;
    }

    //Go to the smaller subproblem.
    printRecursively(n-1, increasing);
    
    //Print away from base case, if you want it to be increasing
    if (increasing) {
        cout << n << " ";
        cout << endl;
    }
}

//Purpose: Recursively search for a target in a vector of integers. 
//The smaller problem is looking at the subvector starting from next element. 
//Input: 1) Vector of integers 2) Target you are looking for. 3) Element to start from.
//Return the index of the leftmost element; -1 if not found.
int findFirstElemRecursively (vector<int> const &vec, int target, int i) {

    //Base cases: You find the element or you reach the end.
    if ( vec[i] == target) {
        return i;
    }

    if ( i == vec.size() ) {
        return -1;
    }

    //Recursion case: Search the vector starting from next element
    return findFirstElemRecursively(vec, target, i+1);
}

//Purpose: Recursively search for all occurrences of a target in a vector of integers. 
//The smaller problem is looking at the subvector starting from next element. 
//Input: 1) Vector of integers 2) Target you are looking for. 3) Element to start from.
//Return the index of the leftmost element; -1 if not found.
vector<int> findAllRecursively(vector<int> const &vec, int target, int i) {

    //Base case: You reach the end
    if (i == vec.size()) {
        vector<int> av = {}; 
        return av;
    }
    
    //Recursive case
    vector<int> rv = findAllRecursively(vec, target, i+1);

    //Away from the base case
    if (vec[i] == target) {
        rv.push_back(i);
    }

    return rv;
}

//Purpose: Recursively find how many different ways you can fit tiles in a board.
//Tile size is 1 x M.
//Board size is N x M.
int calcTilingPermutations(int n, int m) {
    
    //Special case: m or n <= 0
    if (n <= 0 || m <= 0) {
        cout << "Invalid entry in calcTilingPermutations. Terminating. " << endl;
    }

    //Special case: m = 1. You are fitting squares.
    if (m == 1) {
        return 1;
    }

    //Base case: n is less than m. You can only place vertically.
    if (n < m) {
        return 1; 
    }

    //Base case situation #3: n is exactly m. You can stack all these either vertically or horizontally.
    if (n == m) {
        return 2; 
    }

    //Recursion case
    return (calcTilingPermutations(n-1,m)+calcTilingPermutations(n-m,m));
}

//Purpose: Recursively solve the friend party problem. 
//N DISTINGUISHABLE individuals could stay single or pair with another individual.
//In each permutation, each individual can only pair once.
//Return the number of permutations.
int calcFriendPairingParty(int n) {
    //Error case: Improper input.
    if (n <= 0) {
        return 0;
    }
    
    //Base cases: n = 1; Only one possibility, n = 2, either both paired or individual.
    if (n == 1 | n == 2) {
        return n;
    }

    //Recursive case
    //A increase by one individual has two options.
    //If she/he goes unpaired, there are f(N-1) permutations of the remaining ones.
    //If the new friend pairs, she/he can pair with N-1 people. And each pairing has f(N-2) possibilities for the rest.
    return (calcFriendPairingParty(n-1) + (n-1)*calcFriendPairingParty(n-2));
}

//Purpose: Recursively find how many paths from one corner to another in an NxM grid.
//able to move right or down.
int calcGridPaths(int n, int m) {
    //Base case: You are looking at a 1x1 grid.
    if (n == 1 && m == 1) {
        return 1;
    }

    //Special case: 
    //You reach the end of rows. You cannot keep going down.
    //Or you reach the end of columns. You cannot keep going right.
    if ( n <= 0 || m <= 0 ) {
        return 0;
    }

    //Recursion case: Look at the smaller subproblems.
    
    //If you go down: The smaller subgrid has n - 1 rows 
    //If you go right: m -1 columns
    return calcGridPaths(n-1,m) + calcGridPaths(n, m-1);;
}

//Purpose: Helper function for finding the binary permutations of size n without consecutive ones.
//This specific function adds a zero to the end of all strings in the vector.
//Passed by value so that it can be modified without affecting the original.
vector<string> addZerosToStrings(vector<string> vec) {
    vector<string>::iterator it;
    for (it = vec.begin(); it < vec.end(); it++) {
        *(it) = *(it)+"0";
    }
    return vec;
}

//Purpose: Helper function for finding the binary permutations of size n without consecutive ones.
//This specific function deletes strings that end in one, and adds one to the end of the remaining ones.
//Passed by value so that it can be modified without affecting the original.
vector<string> addOnesToStrings(vector<string> vec) {
    
    vector<string>::iterator it = vec.begin();
    while (it < vec.end()) {
        
        //Iterator for checking last character of this element.
        string::iterator si = it->end()-1;

        //If last character is equal to one. Delete this element. Move to next element.        
        if (*si == '1') {
            it = vec.erase(it); //Updates iterator to element that was next to one deleted.
        }
        
        //Otherwise, add 1 and move on to next element.
        else {
            *(it) = *(it)+"1";
            it++;            
        }
    }

    return vec;
}

//Purpose: Find binary string permutations (of size n) without consecutive 1s.
//Examples: n = 1 -> {0,1}; n = 3 -> 000 001 010 100 101
vector<string> findBinaryPermutNoConsecutive1(int n) {
    //Special case: n <= 0
    if (n <= 0) {
        cout << "n must be more than zero" << endl;
    }

    //Base case: Create the vector and start with 0 and 1.
    if (n == 1) {
        vector<string> rv = {"0", "1"};
        return rv;
    }

    //Recursion case: Keep adding elements

    vector<string> addedzero = addZerosToStrings(findBinaryPermutNoConsecutive1(n-1));
    vector<string> addedone = addOnesToStrings(findBinaryPermutNoConsecutive1(n-1));

    //Away from base cases

    //Combine the two and sort
    addedzero.insert(addedzero.end(), addedone.begin(), addedone.end());
    sort(addedzero.begin(), addedzero.end());

    return addedzero;
}

//Purpose: Take two sorted vectors, each of them sorted, and merge them so that the result is also sorted.
//Returns a new, merged, and sorted vector.
//Example: {1,5,6}, {2,3,8} -> {1,2,3,5,6,8}
vector<int> mergeTwoSorted(vector<int> a, vector<int> b) {
    //Return vector.
    vector<int> result;
    
    //Iterators for both vectors.
    vector<int>::iterator ait = a.begin();
    vector<int>::iterator bit = b.begin();

    //Continue until one of the vectors hits the end.
    while (ait != a.end() and bit != b.end() ) {
        //Compare the current element of one vector to the other.
        //Place the smallest of the two into the result vector. Move to next element in the vector that had the smallest.
        if (*ait <= *bit) {
            result.push_back(*ait);
            ait++;
        }
        else {
            result.push_back(*bit);
            bit++;
        }
    }

    //Since you hit the end of one of the vectors first, 
    //the rest from the other vector must be placed into the result.
    //You don't know which one ran out first so do it for both.
    while (ait != a.end()) {
        result.push_back(*ait);
        ait++;
    }
    while (bit != b.end()) {
        result.push_back(*bit);
        bit++;
    }
    return result;
}

//Purpose: merge-sort a vector. 
//Everything done by iterators and by passing by value.
//Returns a new sorted vector.
vector<int> sortByMergePassValue(vector<int> a) {
    int n = a.size();
    std::size_t mid = a.size()/2;

    //Error case: Empty vector was input.
    if (a.empty()) {
        cout << "Error in sortByMergePassValue. Vector is empty. Terminating." << endl;
        return {};
    }

    //Base case: Only one element in the vector. You are done.
    if (n == 1) {
        return a;
    }

    //Break into two subvectors.
    vector<int> left_vector(a.begin(), a.begin()+mid); //The end is not inclusive
    vector<int> right_vector(a.begin()+mid, a.end());

    //Recursively sort each of these vectors.
    left_vector = sortByMergePassValue(left_vector);
    right_vector = sortByMergePassValue(right_vector);

    //Merge the two vectors, which are each sorted.
    return mergeTwoSorted(left_vector, right_vector);
}

//Purpose: Modifies in place. Takes two adjacent sections of a vector, each of which is already sorted, 
//and arranges them so that the two adjacent sections are now sorted.
//Example {1,4,2,6,2,3,2,3} with s = 0 and e = 3 ==> {1,2,4,6,2,3,2,3}.
//Vector of integers (v) is modified in place. Requires a start (int s) and ending index (int e).
//First section starts from s element of the vector v, and ends at (s+e)/2. 
//Second section starts from (s+e)/2 + 1 and ends in e.
void mergeTwoSorted (vector<int> &v, int s, int e) {
    //Temporary vector into which smallest elements will be consecutively placed.
    vector<int> temp;

    //Middle element to separate subsections of the vector that will be merged.
    //Please note that the left/right subsections do not have to span the whole vector.
    //Left subsection: s to mid.
    //Right subsection: mid+1 to e.
    int mid = (s + e)/2;
    
    //Indices.
    int i = s; //Index to sample the left subsection.
    int j = mid + 1; //Index to sample the right subsection.

    //Continue until you exhaust one of the subsections.
    while (i <= mid and j <= e) {
        //Compare elements from each subsection.
        //Place the smallest into the temporary vector. 
        //Move the index in the subsection that had the smallest.
        if (v[i] <= v[j]) {
            temp.push_back(v[i]);
            i++;
        }
        else {
            temp.push_back(v[j]);
            j++;
        }
    }

    //Depending on the original arrangement, 
    //either the left or right subsection may still have remaining elements.    
    
    //In case the left subsection has remaining elements:
    while (i <= mid) {
        temp.push_back(v[i]);
        i++;
    }
    
    //In case the right subsection has remaining elements:
    while (j <= e) {
        temp.push_back(v[j]);
        j++;
    }

    //Modify in place the original by using the temporary vector.
    //Temp should be e-s long, and you need to start from s.
    for (int x = 0; x <= e-s; x++) {
        v[s+x] = temp[x];
    }
}

//Purpose: Perform sort merge in place.
//Vector of integers (v) is modified in place. Requires a start (int s) and ending index (int e).
void sortByMerge (vector<int> &v, int s, int e) {    
    //Base case: No more divisions to make.
    if (s >= e) {
        return;
    }
    
    //Recursion case: Keep dividing.
    
    int mid = (s + e)/2;

    sortByMerge(v, s, mid); //sort the left subsection.
    sortByMerge(v,mid+1,e); //sort the right subsection.

    //Merge the two sorted subsections such that the merge is also sorted.
    return mergeTwoSorted(v,s,e);
}

////Purpose: Perform sort merge in place.
//Overload of function so that only the vector can be inputted. 
void sortByMerge (vector<int> &v) {
    int s = 0;
    int e = v.size() - 1;
    sortByMerge(v, s, e);
}

//Purpose: Helper function for quick sort. 
//Take the first element ("pivot") and arrange the vector in place such that 
//the pivot ends in an ordered-position: All elements less than the pivot are to its left and those greater to its right.
int partition (vector<int> &v, int s, int e) {
    //Use starting element as pivot.
    int pivot = v[s];

    //Indices.
    int i = s; //Starts from the left and looks for elements GREATER than the pivot.
    int j = e; //Starts from the end and looks for elements LESS than the pivot.

    //Move ith to the right and jth to the left until they pass each other.
    while (i < j) {
        
        //ith index will look for elements bigger (or equal) than the pivot.
        //Keep moving until you find one.
        do {
            i++;
        } while (v[i] <= pivot);

        //jth index will look for element smaller than the pivot.
        //Therefore, move left when the element is bigger.
        //Don't move j if the element is equal.  
        do {
            j--;

        } while (v[j] > pivot);
        
        //You have found an ith element bigger than the pivot and a jth element smaller.
        //Only swap if i < j. At the last iteration i may go past j and you don't want to swap these.
        if (i < j) {
            std::swap(v[i],v[j]);
        }
    }

    //Placing the pivot element at the jth position will ensure that everything before is smaller and everything
    //after is bigger.
    std::swap(v[s],v[j]);

    //Return the in-order position.
    return j;
}

//Purpose: quick sort a vector.
//Modifies the vector of integers v in place. Requires a starting index (int s) and ending index (int e).
void quickSort (vector<int> &v, int s, int e) {
    //Base case: Nothing else to partition.
    if (s >= e) {
        return;
    }
    
    //Recursive case: Partition and recursively call the remainders.
    int insorted = partition(v,s,e);

    quickSort(v,s, insorted);
    quickSort(v,insorted+1,e);
}

//Purpose: Overload quicksort so that you can just call the vector without specifying indices.
void quickSort (vector<int> &v) {
    int n = v.size();
    quickSort(v, 0, n);
}
