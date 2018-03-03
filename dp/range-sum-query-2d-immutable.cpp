//Range Sum Query 2D - Immutable
//Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1,
//col1) and lower right corner (row2, col2).
//Range Sum Query 2D
//The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which
//contains sum = 8.
//Example:
//Given matrix = [
//  [3, 0, 1, 4, 2],
//  [5, 6, 3, 2, 1],
//  [1, 2, 0, 1, 5],
//  [4, 1, 0, 1, 7],
//  [1, 0, 3, 0, 5]
//]
//sumRegion(2, 1, 4, 3) -> 8
//sumRegion(1, 1, 2, 2) -> 11
//sumRegion(1, 2, 2, 4) -> 12
//Note:
//You may assume that the matrix does not change.
//There are many calls to sumRegion function.
//You may assume that row1 ≤ row2 and col1 ≤ col2.



//######################################### RowWise running sum #########################################
class NumMatrix {

    int[][] rowWiseRunningSum;
    public NumMatrix(int[][] matrix) {
        int m = matrix.length;
        if(m == 0) return;
        int n = matrix[0].length;
        for(int i=0;i<m;i++)
            for(int j=1;j<n;j++) matrix[i][j] += matrix[i][j-1];
        rowWiseRunningSum = matrix;
    }

    public int sumRegion(int row1, int col1, int row2, int col2) {
        int sum = 0;
        for(int i=row1;i<=row2;i++)
            sum += col1 == 0 ? rowWiseRunningSum[i][col2] : rowWiseRunningSum[i][col2]  - rowWiseRunningSum[i][col1-1];
        return sum;
    }
}


//######################################### Row+ColumnWise running sum #########################################
//  O---X1---X2---X
//  |   |    |    |
//  E---A----D----|
//  |   |    |    |
//  Y1--B----C----|
//    |              |
//  Y-------------X
//|ABCD| = |OY1CX2| - |OY1BX1| - |OEADX2| + |OEAX!|

//1 2 3      1  3  6
//4 5 6  ->  5 12 21
//7 8 9      12 27 45

//Sum(row1,col2)= dp[row2][col2] - dp[row1-1][col2] - dp[row2][col1-1] + dp[row1-1][col1-1]
//

class NumMatrix {

    private int[][] dp;

    public NumMatrix(int[][] matrix) {

        if (null != matrix && 0 != matrix.length) {
            // build the dp array dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1](all in range)
            for (int i = 0; i < matrix.length; i ++)
                for (int j = 0; j < matrix[0].length ; j ++) {
                    if (i - 1 >= 0)
                        matrix[i][j] += matrix[i - 1][j];
                    if (j - 1 >= 0)
                        matrix[i][j] += matrix[i][j - 1];
                    if (i - 1 >= 0 && j - 1 >= 0)
                        matrix[i][j] -= matrix[i - 1][j - 1];
            }
        }
        dp = matrix;

    }

    public int sumRegion(int row1, int col1, int row2, int col2) {

        int sum = dp[row2][col2];
        if (row1 - 1 >= 0)
            sum -= dp[row1 - 1][col2];
        if (col1 - 1 >= 0)
            sum -= dp[row2][col1 - 1];

        return sum += (row1 - 1 >= 0 && col1 - 1 >= 0) ? dp[row1 - 1][col1 - 1] : 0;
    }
}



//######################################### Row+ColumnWise running sum #########################################
//Construct a 2D array sums[row+1][col+1]
//(notice: we add additional blank row sums[0][col+1]={0} and blank column sums[row+1][0]={0} to remove the edge case checking), so, we can have the following definition
//sums[i+1][j+1] represents the sum of area from matrix[0][0] to matrix[i][j]
//
//To calculate sums, the ideas as below
//
//+-----+-+-------+     +--------+-----+     +-----+---------+     +-----+--------+
//|     | |       |     |        |     |     |     |         |     |     |        |
//|     | |       |     |        |     |     |     |         |     |     |        |
//+-----+-+       |     +--------+     |     |     |         |     +-----+        |
//|     | |       |  =  |              |  +  |     |         |  -  |              |
//+-----+-+       |     |              |     +-----+         |     |              |
//|               |     |              |     |               |     |              |
//|               |     |              |     |               |     |              |
//+---------------+     +--------------+     +---------------+     +--------------+
//
//   sums[i][j]      =    sums[i-1][j]    +     sums[i][j-1]    -   sums[i-1][j-1]   +
//
//                        matrix[i-1][j-1]
//So, we use the same idea to find the specific area's sum.
//
//+---------------+   +--------------+   +---------------+   +--------------+   +--------------+
//|               |   |         |    |   |   |           |   |         |    |   |   |          |
//|   (r1,c1)     |   |         |    |   |   |           |   |         |    |   |   |          |
//|   +------+    |   |         |    |   |   |           |   +---------+    |   +---+          |
//|   |      |    | = |         |    | - |   |           | - |      (r1,c2) | + |   (r1,c1)    |
//|   |      |    |   |         |    |   |   |           |   |              |   |              |
//|   +------+    |   +---------+    |   +---+           |   |              |   |              |
//|        (r2,c2)|   |       (r2,c2)|   |   (r2,c1)     |   |              |   |              |
//+---------------+   +--------------+   +---------------+   +--------------+   +--------------+

//######################################### sum adjust  #########################################
class NumMatrix {
private:
    int row, col;
    vector<vector<int>> sums;
public:
    NumMatrix(vector<vector<int>> matrix) {
        row = matrix.size();
        col = row>0 ? matrix[0].size() : 0;
        sums = vector<vector<int>>(row+1, vector<int>(col+1, 0));
        for(int i=1; i<=row; i++) {
            for(int j=1; j<=col; j++) {
                sums[i][j] = matrix[i-1][j-1] +
                             sums[i-1][j] + sums[i][j-1] - sums[i-1][j-1] ;
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return sums[row2+1][col2+1] - sums[row2+1][col1] - sums[row1][col2+1] + sums[row1][col1];
    }
};

//######################################### sum adjust +  diff modification #########################################
class NumMatrix {
public:
    NumMatrix(vector<vector<int>> matrix) {
        accu = matrix;
        for (int i=0; i<matrix.size(); ++i)
            for (int j=0; j<matrix[0].size(); ++j)
                accu[i][j] += a(i-1, j) + a(i, j-1) - a(i-1, j-1); //add (left+top) - diagonal ele
                //or
                //accu[i][j] += a(i, j) - sumRegion(i, j, i, j);
    }

    int sumRegion(int row1, int col1, int row2, int col2) { //i,j,i,j = mat[i][j]
        return a(row2, col2) - a(row1-1, col2) - a(row2, col1-1) + a(row1-1, col1-1);
        // right - top - left + top
    }

private:
    vector<vector<int> > accu;
    int a(int i, int j) {
        return i >= 0 && j >= 0 ? accu[i][j] : 0;
    }
};
/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * int param_1 = obj.sumRegion(row1,col1,row2,col2);
 */

// vim: set sw=2 sts=2 tw=120 et nospell :
