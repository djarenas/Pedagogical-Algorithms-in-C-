#include "Vec2DFunc.h"

namespace Vec2DFunc {

    //Purpose: Print a 1D vector. 
    void printVect(vector<int> &A) {
        vector<int>::iterator it;
        for (it = A.begin(); it < A.end(); it++){
            cout << *(it) << " ";
        }
        cout << endl << endl;
    }

    //Purpose: Print pair of integers.
    void printPair(pair<int,int> &A) {
        cout << A.first << "\t" << A.second << endl;
    }

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

    //Purpose: Print a 2D vector of strings. Variable columns per row accepted.
    void printTwoDVector(vector<vector<string>> &vect) {
        vector<vector<string>>::iterator nit;
        for (nit = vect.begin(); nit < vect.end(); nit++) {
            vector<string>::iterator cit;
            for (cit = nit->begin(); cit < nit->end(); cit++) {
                cout << *cit << "\t";
            }
            cout << endl;
        }
    }

    //Purpose: Take a 2D vector of integers --> Print in spiral form.
    void printSpiral (vector<vector<int>> vect) {
        int n = vect.size();
        int m = vect[0].size();

        //Variables to keep track of the x and y limits.
        int lx = 0; //left
        int rx = m; //right
        int ty = 0; //top
        int by = n; //bottom

        //Continue until the limits meet each other.
        while (lx < rx && ty < by) {
            //Print the top row
            for (int j = lx; j < rx; j++) {
                cout << vect[ty][j] << "\t";
            }
            //The right column.
            for (int i = ty+1; i < by; i++) {
                cout << vect[i][rx-1] << "\t";
            }
            //Bottom row.
            for (int j = rx-2; j > lx; j--) {
                cout << vect[by-1][j] << "\t";
            }
            //Left column.
            for (int i = by-1; i > ty; i--) {
                cout << vect[i][lx] << "\t";
            }

            //Update the x and y limits.
            lx++;
            rx--;
            ty++;
            by--;
        }
    }

    //Purpose: Check that a 2D vector has n rows and m columns.
    bool checkDimensionality (vector<vector<int>> &v2D, int n, int m) {
        
        //Check it has the right number of rows.
        if (v2D.size() != n) {
            cout << "Error in checkDimensionality. Number of rows in 2D vector was not what was expected." << endl;
            cout << "Terminating." << endl;
            
            return false;
        }

        //Check each row to see if it has the right number of columns.
        for (int i = 0; i < n; i++) {
            if (v2D[i].size() != m) {
                cout << "Error in checkDimensionality" << endl;
                cout << "Row #" << i << " did not have the desired number of columns" << endl;
                cout << "Terminating." << endl;
                
                return false;
            }
        }

        //No errors found
        return true;
    }

    //Purpose: nxm 2D vector --> 1D vector saved as a reverse wave.
    //{{1, 3, 5}
    // {2, 4, 6}} --> {5,6,3,4,1,2}
    vector<int> saveReverseWave(vector<vector<int>> &vect) {

        vector<int> rv = {}; //Return variable.

        //Size of the 2D array.
        int n = vect.size();
        int m = vect[0].size();

        //Keep track of right limit and direction.
        bool down = true;
        int x = m-1;

        while (x >= 0) {
            if (down) {
                for (int i = 0; i < n; i++) {
                    rv.push_back(vect[i][x]);
                }
            }
            if (!down) {
                for (int i = 0; i < n; i++) {
                    rv.push_back(vect[n-1-i][x]);
                }
            }
            down = !down;
            x--;
        }
        return rv;
    }

    //Purpose: Take a sorted 2D vector and search for a wanted integer. 
    //Takes advantage of 2D architecture.
    //The function works even for variable columns per row. 
    //Input: 1) Sorted 2D vector 2) Target integer. 
    //Returns {i,j} (pair) as the location of the found integer. Returns {-1,-1} if not found.
    pair<int,int> searchSorted2DVector(vector<vector<int>> vect, int x) {

        //Check very first element. If target is less, return {-1,-1}.
        if (x < vect[0][0]) {
            return (make_pair(-1,-1));
        }

        //Explore each row.
        vector<vector<int>>::iterator nit;       
        for (nit = vect.begin(); nit < vect.end(); nit++) {
            //Column iterator.
            vector<int>::iterator cit;

            //Check that the target is equal or bigger than the starting element.
            cit = nit->begin();
            int rowbeg = *(cit);
            //If not, you should have found it by now. Return -1,-1.
            if (x < rowbeg) {
                return (make_pair(-1,-1));
            }
            //If the same as target return this location.
            if (rowbeg == x) {
                return make_pair(nit-vect.begin(), cit - nit->begin());
            }

            //Check the end of the row
            cit = nit->end()-1;
            int rowend = *(cit);
            //Return if equal to target.
            if (rowend == x) {
                return make_pair(nit-vect.begin(), cit - nit->begin());
            }
            
            //If the target lies within this row, check each element.
            if (x > rowbeg && x < rowend) {
                for (cit = nit->begin(); cit < nit->end(); cit++) {
                     if (*cit == x) {
                        return make_pair(nit-vect.begin(), cit - nit->begin());
                     }
                }
                //If it was not equal to any element in this row, then it is not in the array.
                return (make_pair(-1,-1));
            }
        }

        //You have made it to last row.
        return make_pair(-1,-1);
    }

    //Purpose: Return up to the nth row of the Pascal Triangle
    //Returns a 2D vector.
    vector<vector<int>> calcPascalTriangle(int n) {
        vector<vector<int>> rv; //Return 2D vector.

        //P(1): First row is just one vector with one element equal to one.
        rv.push_back({1});

        //P(N)
        for (int i = 1; i < n; i++) {
            //Add a null vector for this new row
            rv.push_back({});
            
            for (int j = 0; j <= i; j++) {
                //Always start with one and end with one.
                if (j == 0 || j == i) {
                    rv[i].push_back(1);
                }
                
                //Find component by adding consecutive elements in prevous row
                else {
                    rv[i].push_back(rv[i-1][j]+rv[i-1][j-1]);
                }
            }
        }
        return rv;
    }

    //Purpose: Calculate the sum inside a smaller inner portion of the 2D-vector
    //Input 1) 2D vector of integers
    //2) Coordinates that define the inner portion: Starting row, column, ending row, column.
    //The starting and ending points are inclusive.
    int calcSub2DSum (vector<vector<int>> vect, int sr, int sc, int er, int ec) {
        //Find prefix sum.
        int r = 0;
        
        for (int i = sr; i <= er; i++) {
            for (int j = sc; j <= ec; j++) {
                r += vect[i][j];
            }
        }
        return r;
    }

    //Purpose: Take a 2D NxN vector of integers and get the perimeter of inner loops.
    //Input: 1) 2D NxN vector of integers. 2) Desired inner loop.
    //Example: {{1,2,3}, {4,5,6}, {7,8,9}}
    //Outer loop (l = 0) would have a perimeter of {1,2,3,6,9,8,7,4};
    //Inner loop (l = 1) would have a perimeter of {5};
    vector<int> getPerimeter (vector<vector<int>> &v2D, int loop) {
        vector<int> rv = {}; //Return variable. Will return empty if there were errors.

        //Check dimensionality of the 2D vector.
        int n = v2D.size();
        if (!checkDimensionality(v2D, n, n)) {
            cout << "Error in getPerimeter. Not a NxN vector." << endl;
            cout << "Terminating." << endl;
            return rv;
        }

        //Special cases: Only one element in this loop.
        if (n-2*loop == 1) {
            rv.push_back(v2D[0+loop][loop]);
            return rv;
        }
        
        //Special case: 4 elements left inside the loop.
        //You only need to get two rows.
        if (n-2*loop == 2) {
            //Get top row
            for (int i = 0+loop; i < n-loop; i++) {
                rv.push_back(v2D[0+loop][i]);
            }
            //Get bottow row
            for (int i = n-1-loop; i >= 0 + loop; i--) {
                rv.push_back(v2D[n-loop-1][i]);
            }
            return rv;
        }

        //Other cases: More than 9 elements left inside the loop

        //Get top row
        for (int i = 0+loop; i < n-loop; i++) {
            rv.push_back(v2D[0+loop][i]);
        }
        //Get end column
        for (int i = 1+loop; i < n-loop; i++) {
            rv.push_back(v2D[i][n-1-loop]);
        }
        //Get bottow row
        for (int i = 1+loop; i < n-loop; i++) {
            rv.push_back(v2D[n-1-loop][n-1-i]);
        }
        //Get starting column
        for (int i = 1+loop; i < n-1-loop; i++) {
            rv.push_back(v2D[n-1-i][0+loop]);
        }

        return rv;
    }

    //Purpose: Take a vector of integers and move each element to the right by a set amount of steps.
    //Outputs a new vector.
    vector<int> shiftVector(vector<int> inputvec, int shift) {
        int n = inputvec.size();
        vector<int> outputvec(n,0); //Return vector.

        for (int i = 0; i < n; i++) {
            outputvec[(i+shift)%n] = inputvec[i];
        }
        return outputvec;
    }

    //Purpose: Updates a 2-dimensional NxN with a new outer loop or inner loop.
    //Input: 1) NxN two-dimensional array (a vector of vector of integers).
    //2) A vector with the new perimeter you want. The size must be 4*(n-loop-1).
    //3) The loop you want to update. Zero for outer, one for the next inner loop, ...
    //Modifies the 2D vector in place.
    void updateWithNewPerimeter(vector<vector<int>> &v2D, vector<int> perimeter, int loop) {
        //Check 2D-vector size
        int n = v2D.size();

        //Check NxN symmetry.
        if (!checkDimensionality(v2D, n, n)) {
            cout << "Error in updateWithNewPerimeter. 2D-vector is not symmetric." << endl;
            cout << "Terminating." << endl;
            return;
        }
        
        //Desired loop cannot be above (N+1)/2 (as integer division)
        if (loop >= (n+1)/2) {
            cout << "Error in updateWithNewPerimeter. Desired inner loop is too big compared to size." << endl;
            cout << "Terminating." << endl;
            return;
        }

        //Check that the perimeter input vector has the correct size.
        //The outer loop should have a perimeter of 4*(n-1). First inner loop: 4*(n-2-1),...
        if (perimeter.size() != 4*(n-2*loop-1)) {
            cout << "Warning: The perimeter you are trying to update is not the right size" << endl;
            return;
        }

        //Counter for the perimeter vector
        int j = 0;

        //You need to update the top row, right column, bottow row, and left column of the inner loop.
        
        //Set top row
        for (int i = 0+loop; i < n-loop; i++) {
            v2D[0+loop][i] = perimeter[j];
            j++; 
        }
        
        //Set end column
        for (int i = 1+loop; i < n-loop; i++) {
            v2D[i][n-1-loop] = perimeter[j];
            j++;
        }
        
        //Set bottow row
        for (int i = 1+loop; i < n-loop; i++) {
            v2D[n-1-loop][n-1-i] = perimeter[j];
            j++;
        }
        
        //Set starting column
        for (int i = 1+loop; i < n-1-loop; i++) {
            v2D[n-1-i][0+loop]=perimeter[j];
            j++;
        }
    }

    //Purpose: Takes a symmetric 2D-vector of integers and rotate it by a desired amount.
    //It recursively rotates loop by loop until it makes it to the middle.
    //Input: 1) Symmetric 2D vector of integers. 
    //2) Angle you want to rotate in degrees.
    //3) Counter for loops to be used in recursion. Use zero when you call it. 
    void rotate2DByPerimeter(vector<vector<int>> &v2D, int degrees, int loop) {
        int n = v2D.size();

        //Base case: loop is bigger than n/2. You have no more inner loops to rotate.
        if (loop >= n/2) {
            return;
        }
    
        //Recursive case:
        //Rotate current loop and then call to rotate the next inner one.
        
        //Get perimeter of this loop.
        vector<int> perimeter = getPerimeter(v2D, loop);
        
        //Rotate the perimeter by shifting the appropriate amount.
        //Calculate how much you have to shift each element in the perimeter to obtain the desired angle
        //Shift every element in the perimeter by that amount.
        int shift = 4*(n-1-2*loop)*degrees/360; 
        perimeter = shiftVector(perimeter, shift);

        //Update the perimeter of the current loop with the newly shifted
        updateWithNewPerimeter(v2D, perimeter, loop);

        //Move to next inner loop
        rotate2DByPerimeter(v2D, degrees, loop + 1);
    }

    //Purpose: Print a NxN vector of integers after rotating by customizable account. 
    //0-360 degrees.
    void printRotatedTwoDVector(vector<vector<int>> vect, int degrees) {
        int n = vect.size();

        //Check NxN
        if (!checkDimensionality(vect, n, n)) {
            cout << "Error in printSymmetricTwoDVector. Not NxN." << endl;
            cout << "Terminating." << endl;
            return;
        }

        //Rotate 
        Vec2DFunc::rotate2DByPerimeter(vect, degrees, 0);
        
        //Print
        Vec2DFunc::printTwoDVector(vect);
        
        return;
    }
                                                                 
    //Purpose: Print a vector of cartesian points.
    void printCartesianVector(vector<pair<int, int>> pointvector) {
        int n = pointvector.size();
        
        for (int i = 0; i < n;i++) {
            cout << "(" << pointvector[i].first << ", " << pointvector[i].second \
            << ")\t";
        }
        cout << endl;
    }

    //Purpose: Compares two cartesian points (pair of integers)
    //By x (first), and if x is the same, by y (second).
    //Returns true if point 1 is less or equal to point 2.
    bool compareCartesian(pair<int, int> p1, pair<int, int> p2) {
        //Compares x first
        if (p1.first < p2.first) {
            return true;
        }
        if (p1.first > p2.first) {
            return false;
        }

        //If x are equal, then compare by y.
        if (p1.first == p2.first) {
            if (p1.second > p2.second) {
                return false;
            }
        }

        return true;
    }

    //Purpose: Find distance between two cartesian points.
    //Input: 1) Pair of integers. 2) Pair of integers.
    double calcTwoPointsDistance(pair<int, int> p1, pair<int, int> p2) {
        double res = sqrt(pow(p2.first - p1.first, 2) + pow(p2.second - p1.second, 2));
        return res;
    }

    //Purpose: Compare which of two points is closest to a third point
    bool compareDistanceToOrigin(pair<int, int> p1, pair<int, int> p2) {
        pair<int,int> origin = make_pair(0,0);

        if (calcTwoPointsDistance(p1,origin) <= calcTwoPointsDistance(p2,origin)) {
            return true;
        }
        else {
            return false;
        }

    }

    //Purpose: Build a w x h grid of cartesian points. 
    //Input : 1) Width of the grid. 2) Height of the grid.
    //Returns a vector of cartesian points (as integer pairs).
    vector<pair<int,int>> buildGrid(int w, int h) {   
        vector<pair<int,int>> gridvec = {}; //Return variable.
        
        for (int i = 0; i < w;i++) {
            for (int j = 0; j < h; j++) {
                gridvec.push_back({i,j});
            }
        }
        
        return gridvec;
    }

    //Purpose: In a chess board with adjustable width and height, and a variable 
    //amount of rooks, calculate the largest area undefended by the rooks.
    //Inputs 1) Board Width. 2) Board Height. 3) A vector with the cartesian positions of the rooks.
    int calcPenaltyDefenseKingdom(int w, int h, vector<pair<int, int>> position) {
        
        //Make vectors that contain the limits of the board and the lines protected by the rooks.
        vector<int> xlimits = {0, w+1}; //Start with the limits of the board.
        vector<int> ylimits = {0, h+1}; //Start with the limits of the board.
        
        //Add to these vectors the positions of the rooks. 
        vector<pair<int,int>>::iterator it;
        //Each position in the vector received by the function.
        for (it = position.begin(); it != position.end(); ++it) {   
            xlimits.push_back((*it).first);
            ylimits.push_back((*it).second);
        }
        
        //Sort the x and y limits
        sort(xlimits.begin(), xlimits.end());
        sort(ylimits.begin(), ylimits.end());

        //Find the spaces between the x limits
        vector<int> xspaces = {};
        for (vector<int>::iterator it = xlimits.begin()+1; it != xlimits.end(); it++) {
            xspaces.push_back(*(it) - *(it-1) - 1);
        }
        
        //Find the spaces between the y limits
        vector<int> yspaces = {};
        for (vector<int>::iterator it = ylimits.begin()+1; it != ylimits.end(); it++) {
            yspaces.push_back(*(it) - *(it-1) - 1);
        }
        
        //Sort the x and y spaces. 
        sort(xspaces.begin(), xspaces.end());
        sort(yspaces.begin(), yspaces.end());

        //Find the maximum area by multiplying the maximum x and y spaces.
        return xspaces.back()*yspaces.back();

    }

}