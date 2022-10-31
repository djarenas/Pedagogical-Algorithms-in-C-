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

namespace Vec2DFunc {
    
    void printVect (vector<int> &A);
    void printPair(pair<int,int> &A);
    void printTwoDVector(vector<vector<int>> &vect);
    void printTwoDVector(vector<vector<string>> &vect);
    void printSpiral (vector<vector<int>> vect);
    bool checkDimensionality (vector<vector<int>> &v2D, int n, int m);
    vector<int> saveReverseWave (vector<vector<int>> &vect);
    pair<int,int> searchSorted2DVector(vector<vector<int>> vect, int x);
    vector<vector<int>> calcPascalTriangle(int n);
    int calcSub2DSum (vector<vector<int>> vect, int sr, int sc, int er, int ec);
    vector<int> getPerimeter (vector<vector<int>> &v2D, int loop);
    vector<int> shiftVector(vector<int> inputvec, int shift);
    void updateWithNewPerimeter(vector<vector<int>> &v2D, vector<int> perimeter, int loop);
    void rotate2DByPerimeter(vector<vector<int>> &v2D, int degrees, int loop);
    void printRotatedTwoDVector(vector<vector<int>> vect, int degrees);
    void printCartesianVector(vector<pair<int, int>> pointvector);
    bool compareCartesian(pair<int, int> p1, pair<int, int> p2);
    double calcTwoPointsDistance(pair<int, int> p1, pair<int, int> p2);
    bool compareDistanceToOrigin (pair<int, int> p1, pair<int, int> p2);
    vector<pair<int,int>> buildGrid (int w, int h);
    int calcPenaltyDefenseKingdom(int w, int h, vector<pair<int, int>> position);

}
