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
