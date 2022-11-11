#include "backtracking.h"

//Purpose: Print a 2D vector of integers. Variable columns per row accepted.
void printTwoDVector(vector<vector<int>> &vect) {
    vector<vector<int>>::iterator nit;
    for (nit = vect.begin(); nit < vect.end(); nit++) {
        vector<int>::iterator cit;
        for (cit = nit->begin(); cit < nit->end(); cit++){
            cout << *cit << "\t";
        }
        cout << endl;
    }
}

//Purpose: Builds a grid, as a 2D NxN vector of integers, full of zeros. 
//Returns the 2D vector.
vector<vector<int>> buildBoard(int n) {
    vector<vector<int>> board(n, vector<int> (n,0));
    return board;
}

//Purpose: Checks if placing a queen at (x,y) results in horizontally threatening
//another queen somewhere else in the board.
//Input: 1) The board as a 2D vector. 2,3) The x and y positions you want to check.
//Returns true if placement would result in a threat.
bool checkHorizontalThreats(vector<vector<int>> &board, int x, int y) {
    int n = board.size();

    //Check same column.
    for (int i = 0; i < n; i++) {
        if (board[i][y] == 1) {
            return true;
        }
    }
    return false;
}

//Purpose: Checks if placing a queen at (x,y) results in vertically threatening
//another queen somewhere else in the board.
//Input: 1) The board as a 2D vector. 2,3) The x and y positions you want to check.
//Returns true if placement would result in a threat.
bool checkVerticalThreats(vector<vector<int>> &board, int x, int y) {
    int n = board.size();

    //Check same row.
    for (int i = 0; i < n; i++) {
        if (board[x][i] == 1) {
            return true;
        }
    }
    return false;
}

//Purpose: Checks if placing a queen at (x,y) results in diagonally threatening
//another queen somewhere else in the board.
//Input: 1) The board as a 2D vector. 2,3) The x and y positions you want to check.
//Returns true if placement would result in a threat.
bool checkDiagonalThreats(vector<vector<int>> &board, int x, int y) {
    int tempx;
    int tempy;
    int n = board.size();

    //Check 45 degree angle: rows and columns increase together.
    //Increase row and column together. Check for ones.
    //Set starting points.
    tempx = x;
    tempy = y;
    while (tempx < n && tempy < n) {
        if (board[tempx][tempy] == 1) {
             return true;
        }
        tempx++;
        tempy++;
    }

    //Check 135 degree angle: Rows decrease while columns increase.
    //Set starting points.
    tempx = x;
    tempy = y;
    while (tempx >= 0 && tempy < n) {
        if (board[tempx][tempy] == 1) {
             return true;
        }
        tempx--;
        tempy++;
    }

    //Check 225 degree angle: Rows and columns both decrease.
    //Set starting points.
    tempx = x;
    tempy = y;
    while (tempx >= 0 && tempy >= 0) {
        if (board[tempx][tempy] == 1) {
             return true;
        }
        tempx--;
        tempy--;
    }

    //Check 315 degree angle: Rows and columns both decrease.
    //Set starting points.
    tempx = x;
    tempy = y;
    while (tempx < n && tempy >= 0) {
        if (board[tempx][tempy] == 1) {
             return true;
        }
        tempx++;
        tempy--;
    }

    return false;
}

//Purpose: Checks if placing a queen at (x,y) results in threatening another on the board.
//Returns false if a queen at that position does not threaten any other units in the board.
bool checkQueenThreats(vector<vector<int>> &board, int x, int y) {
    bool threats = false;

    threats = threats || checkHorizontalThreats(board, x, y);
    threats = threats || checkVerticalThreats(board, x, y);
    threats = threats || checkDiagonalThreats(board, x, y);

    return threats;
}

//Purpose: Recursively solve the N queens problem. 
//In a NxN board, place queens such that they are not threatening each other (i.e. able to kill another in only one move). 
// Input: 1) The nxn board by reference (2D vector of integers).
// 2,3) Two integers to keep track of the board as the function works recursively. 
// 4) An integer, passed by reference, that keeps track of how many boards 
// were found that solve the N-Queen problem.
bool solveNQueensByRow(vector<vector<int>> &board, int i, int j, int &sum) {
    //Enforce a size limit.
    int n = board.size();
    if (n > 10) {
        cout << "A board bigger than 10x10 is too computationally expensive. Terminating." << endl;
        return false;
    }
    
    bool threats;
    
    //Base case #1: You made it to last row because you found a successful arrangement of queens.
    if (i == n) {
        //Print the board
        printTwoDVector(board);
        cout << endl;
        
        //Update the variable of how many successful permutations you have found.
        sum++;
        return true;
    }

    //Recursive case

    while (j < n) {
        //cout << endl << i << "\t" << j << endl << endl;
        threats = checkQueenThreats(board, i, j);

        if (!threats) {
            //Place the Queen here.
            board[i][j] = 1;
            
            //Call next row. Give it j = 0 so that the next row always starts from first column.
            bool goodrow = solveNQueensByRow(board, i+1,0,sum);

        }
        //Backtrack:
        //Erase the queen you placed.
        board[i][j] = 0;
        //Move to next column in this row.
        j++;
    }

    return false;
}

//Purpose: Helper function for solving sudoku board.
//Check if you can place a number x in position (i,j) of a sudoku board.
//This specific function checks the row and column. Returns true if you can place it.
bool checkSudokuRowColumn(vector<vector<int>> &board, int x, int i, int j) {
    int n = board.size();
    
    //Check the row and return false if there is a duplicate of x.
    for (int c = 0; c < n; c++) {
        if (x == board[i][c]) {
            return false;
        }
    }

    //Check the column and return false if there is a duplicate of x.
    for (int r = 0; r < n; r++) {
        if (x == board[r][j]) {
            return false;
        }
    }
    
    //No duplicates were found -> You can place number in that position.
    return true;
}

//Purpose: Helper function for solving sudoku board.
//Check if you can place a number x in position (i,j) of a sudoku board.
//This specific function checks the local 3x3 grid.
bool checkSudokuLocal(vector<vector<int>> &board, int x, int i, int j) {
    //Calculate the starting row and column for local 3x3 grid.
    int sr = 3*(i/3); //The integer division ignores remainders.
    int sc = 3*(j/3); 

    //Check all values in the 3x3 grid.
    vector<int> localgrid;
    for (int i = sr; i < sr+3; i++) {
        for (int j = sc; j < sc+3; j++) {
            if (board[i][j] == x) {
                return false;
            }
        } 
    }

    //No duplicates were found -> You can place number in that position.
    return true;
}

//Purpose: Helper function for solving sudoku board.
//Find the next empty element (as a vector {i,j}).
vector<int> findNextEmptyElement(vector<vector<int>> &board, int i, int j) {
    int n = board.size();
    
    bool boardend = false;

    //If the current element is not a zero, and you are not at the end, move to the next.
    while (!boardend && board[i][j] != 0) {
        //Increase the column unless you are at the end of the row.
        if (j < n-1) {
            j++;
        }
        //Move to next row if you are at the last column.
        else if (i < n -1) {
            j = 0;
            i++;
        }
        //Update you are at the end of the board if you are at last column and row.
        if (i == n-1 && j==n-1) {
            boardend = true;
        }
    }
    
    return {i,j};
}

//BOARD EXAMPLE (From Wikipedia)
// vector<vector<int>> sudokuboard = {{5,3,0,0,7,0,0,0,0}, 
//                             {6,0,0,1,9,5,0,0,0}, 
//                             {0,9,8,0,0,0,0,6,0}, 
//                             {8,0,0,0,6,0,0,0,3}, 
//                             {4,0,0,8,0,3,0,0,1}, 
//                             {7,0,0,0,2,0,0,0,6}, 
//                             {0,6,0,0,0,0,2,8,0}, 
//                             {0,0,0,4,1,9,0,0,5}, 
//                             {0,0,0,0,8,0,0,7,9}};


//Purpose: Recursively solve the sukoku board. 
//Board is modified in place. 
//Input: 1) Sudoku board as a 2D vector of integers. Empty elements as zeros.
//2,3) Indices for row and column as the problem is solved recursively. Start from 0,0. 
//4) Modifies in place a collection of the board solutions. 3D vector of integers -> A vector of the 2D boards.
void solveSudokuBoard(vector<vector<int>> &board, int i, int j, vector<vector<vector<int>>> &solutions) {

    int n = board.size();
    
    //Find the next element that is empty.
    vector<int> a = findNextEmptyElement(board,0,0);
    i = a[0];
    j = a[1];

    //Base case: You made it to the end and the board is full and solved.
    //If the board is unsolvable, you don't get this far. 
    if (i == n-1 && j == n-1) {
        //Print the answer
        cout << endl;
        printTwoDVector(board);
        cout << endl;

        //Update the 3D-vector solutions with this solved board (2D-vector).
        solutions.push_back(board);

        return;
    }

    //Recursion case: You haven't made it to the end of the board and there are still numbers to try.

    //Try all possible numbers: 1-9 at this location.
    for (int x = 1; x <= 9; x++) {
        //Check that this number can be placed here without having a repeat in the row or column.
        bool success = checkSudokuRowColumn(board,x,i,j);
        
        //Check that this number can be placed without duplicates in the local 3x3 grid.
        success = success && checkSudokuLocal(board,x,i,j);

        //If it can be placed, place it and call the subproblem.
        if (success) {
            board[i][j] = x;

            //Subproblem is to now fill the board with the updated value
            solveSudokuBoard(board, i+1, j, solutions);    
        }

        //You are here because the recursions you called came back after trying all numbers.
        //Delete the element at this i,j so this recursion can try other numbers.
        board[i][j] = 0;

    }

    return;
}
