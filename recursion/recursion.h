#include <algorithm>
#include <array>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

void printTwoDVector(vector<vector<int>> &vect);
vector<vector<int>> buildBoard (int n);
bool checkHorizontalKills(vector<vector<int>> &board, int x, int y);
bool checkVerticalKills(vector<vector<int>> &board, int x, int y);
bool checkDiagonalKills(vector<vector<int>> &board, int x, int y);
bool checkQueenKills (vector<vector<int>> &board, int x, int y);
bool solveNQueensByRow (vector<vector<int>> &board, int i, int j, int &sum);
bool checkSudokuRowColumn (vector<vector<int>> &board, int x, int i, int j);
bool checkSudokuLocal (vector<vector<int>> &board, int x, int i, int j);
vector<int> findNextEmptyElement (vector<vector<int>> &board, int i, int j);
void solveSudokuBoard(vector<vector<int>> &board, int i, int j, vector<vector<vector<int>>> &solutions);
void printCharArray (char *c, int n);
void buildStringPermutations (char *input, int n, int i, vector<string> &voutput);
