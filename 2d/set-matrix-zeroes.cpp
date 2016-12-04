//Set Matrix Zeroes
//Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.
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
