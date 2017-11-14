//Set Matrix Zeroes
//Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.


//######################################### 2 traversals (L-R),(R-L) ######################################### 
public void setZeroes(int[][] matrix) {
    int m = matrix.length, n = matrix[0].length, k = 0;
    // First row has zero?
    while (k < n && matrix[0][k] != 0) ++k;
    // Use first row/column as marker, scan the matrix
    for (int i = 1; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (matrix[i][j] == 0)
                matrix[0][j] = matrix[i][0] = 0;
    // Set the zeros
    for (int i = 1; i < m; ++i)
        for (int j = n - 1; j >= 0; --j)
            if (matrix[0][j] == 0 || matrix[i][0] == 0)
                matrix[i][j] = 0;
    // Set the zeros for the first row
    if (k < n) Arrays.fill(matrix[0], 0);
}

//######################################### 2 traversals (L-R),(R-L) ######################################### 
//store states of each row in the first of that row, and store states of each column in the first 
//of that column. Because the state of row0 and the state of column0 would occupy the same cell, I let it be the state of row0,
//and use another variable "col0" for column0. In the first phase, use matrix elements to set states in a top-down way. In the second phase, use states to set matrix elements in a bottom-up way.
void setZeroes(vector<vector<int> > &matrix) {
    int col0 = 1, rows = matrix.size(), cols = matrix[0].size();
    for (int i = 0; i < rows; i++) { //L-R
        if (matrix[i][0] == 0) col0 = 0;
        for (int j = 1; j < cols; j++)
            if (matrix[i][j] == 0)
                matrix[i][0] = matrix[0][j] = 0;
    }

    for (int i = rows - 1; i >= 0; i--) {
        for (int j = cols - 1; j >= 1; j--)
            if (matrix[i][0] == 0 || matrix[0][j] == 0)
                matrix[i][j] = 0;
        if (col0 == 0) matrix[i][0] = 0;
    }
}


//######################################### 2 traversals (L-R),(R-L) ######################################### 
void setZeroes(vector<vector<int> >& matrix) {
      int m = matrix.size();
      int n = matrix[0].size();
      bool is_col_zero = false;
      for(int i=0;i<m;i++) {
          if(matrix[i][0] == 0) {
              is_col_zero = true;
          }
          for(int j=1;j<n;j++) {
              if(matrix[i][j] == 0) { 
                matrix[i][0] = 0;
                matrix[0][j] = 0;
              }
          }
      }
     
     for(int i=m-1;i>=0;i--) {
         for(int j=n-1;j>=1;j--) {
             if(matrix[i][0] == 0 || matrix[0][j] == 0) {
                 matrix[i][j] = 0;
             }
         }
     }
    if(is_col_zero) {
        for(int i=0;i<m;i++) {
            matrix[i][0] = 0;
        }
    } 
}

//######################################### Ugly solution  ######################################### 
class Solution {
    public void setZeroes(int[][] matrix) {
        int m = matrix.length;
        int n = matrix[0].length;
        boolean isRowZero = false;
        boolean isColZero = false;
         if(isRowZero == false) {
            int i=0, j=0;
            while(i<m) if(matrix[i++][0] == 0) isRowZero = true;
            while(j<n) if(matrix[0][j++] == 0) isColZero = true;
        }
        
        for(int i=0;i<m;i++) {
            for(int j=1;j<n;j++) {
                if(matrix[i][j] == 0) {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }
        for(int i=1;i<m;i++) {
            if(matrix[i][0] == 0) {
                int j = 0;
                while(j<n) matrix[i][j++] = 0;
            }
        }
         for(int j=1;j<n;j++) {
            if(matrix[0][j] == 0) {
                int i = 0;
                while(i<m) matrix[i++][j] = 0;
            }
        }
        
        if(isRowZero == true) {
            int i=0;
            while(i<m) matrix[i++][0] = 0;
          
        }
        if(isColZero == true) {
            int j =0;
            while(j<n) matrix[0][j++] = 0;
        }
    }
}


//######################################### 2 traversals (L-R),(R-L) python ######################################### 
def setZeroes(self, matrix):
    # First row has zero?
    m, n, firstRowHasZero = len(matrix), len(matrix[0]), not all(matrix[0])
    # Use first row/column as marker, scan the matrix
    for i in xrange(1, m):
        for j in xrange(n):
            if matrix[i][j] == 0:
                matrix[0][j] = matrix[i][0] = 0
    # Set the zeros
    for i in xrange(1, m):
        for j in xrange(n - 1, -1, -1):
            if matrix[i][0] == 0 or matrix[0][j] == 0:
                matrix[i][j] = 0
    # Set the zeros for the first row
    if firstRowHasZero:
        matrix[0] = [0] * n


