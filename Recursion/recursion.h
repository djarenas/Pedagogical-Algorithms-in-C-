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


void printVect(vector<int> &A);
void printVect(vector<string> &A);
void goHome(int x1, int x2);
unsigned long long calcFactorial(int n);
int calcFibonacci(int n);
long long calcPowerRecursively(int x, int p);
long long calcPowerOptimized (int x, int p);
void printRecursively(int n, bool increasing);
int findFirstElemRecursively (vector<int> const &vec, int target, int i);
vector<int> findAllRecursively (vector<int> const &vec, int target, int i);
int calcTilingPermutations(int n, int m);
int calcFriendPairingParty(int n);
int calcGridPaths(int n, int m);
vector<string> addZerosToStrings( vector<string> vec);
vector<string> addOnesToStrings(vector<string> vec);
vector<string> findBinaryPermutNoConsecutive1 (int n);
