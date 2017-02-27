//Search a 2D Matrix
//Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:
//Integers in each row are sorted from left to right.
//The first integer of each row is greater than the last integer of the previous row.
//For example,
//Consider the following matrix:
//[
//  [1,   3,  5,  7],
//  [10, 11, 16, 20],
//  [23, 30, 34, 50]
//]
//Given target = 3, return true.


//###################################### Assume 2d matrix as a linear array ######################################  
bool searchMatrix(vector<vector<int>>& matrix, int target) { 
  if(matrix.empty()) {
        return false;
    } 
  int rows = matrix.size();
  int cols = matrix[0].size();
  int s = 0, e = rows* cols - 1;
  
  while(s<=e) {
      int m = s+(e-s)/2; 
      if(matrix[m/cols][m%cols] == target) { //3*4 - 1
          return true;
      }else if(matrix[m/cols][m%cols]>target) { 
          e = m -1; //left of key element
      }else {
          s = m + 1; //right of key element
      }
  }
  return false;
}


//###################################### Search in 2-d ######################################  
//1. Search possible row O(log n)
//2. BS in entire possible row O(log n)
bool searchMatrix(vector<vector<int>>& matrix, int target) { 
  if(matrix.empty() || matrix.front().empty()) {
    return false;
  }
  //Row search 
  //u : total row count
  int l = 0, u = matrix.size() - 1, r = -1;
  while (l <= u) {
      int m = l + (u - l) / 2;
      if (matrix[m][0] <= target) {
          r = m; //update the possible row
          l = m + 1;
      } else {
          u = m - 1;
      }
  }
  if (r == - 1) { 
    return false; 
  }
  //simple linear binary search
  l = 0, u = matrix.front().size() - 1;
  while (l <= u) {
      int m = l + (u - l) / 2;
      if (matrix[r][m] == target) {
          return true;
      } else if (matrix[r][m] < target) {
          l = m + 1;
      } else {
          u = m - 1;
      }
  }
  return false; 
}
