//Search a 2D Matrix II
//Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:
//Integers in each row are sorted in ascending from left to right.
//Integers in each column are sorted in ascending from top to bottom.
//For example,
//Consider the following matrix:
//[
//  [1,   4,  7, 11, 15],
//  [2,   5,  8, 12, 19],
//  [3,   6,  9, 16, 22],
//  [10, 13, 14, 17, 24],
//  [18, 21, 23, 26, 30]
//]
//Given target = 5, return true.
//Given target = 20, return false.
#include "../headers/global.hpp"
//#########################  use secondary diagnonal to search
//O(m+n)
bool searchMatrix(vector<vector<int>>& matrix, int target) {
   if(matrix.empty() || matrix.front().empty()) {
    return false;
  }
  vector<pair<int,int> > dirs( { {-1,0},{0,1} } );
  int m = matrix.size();
  int n = matrix.front().size();
  int idx = m;
  int r = 0;
  int c = n-1; //idx starts from zero
  while (r < m && c >= 0) {
    if (matrix[r][c] == target) { 
      return true;
    } else if (matrix[r][c] > target) { 
      c -= 1;
    } else {
      r += 1;
    }
  }
  return false;
}
//################################## Dandc : Ham-sandwhich tree analysis ################################## 
bool searchMatrix(vector<vector<int>>& matrix, int target) { 
  if(matrix.empty() || matrix.front().empty()) {
    return false;
  }
  return searchRect(matrix,target,0,0,matrix.size()-1,matrix.front().size()-1); 
}
bool searchRect(vector<vector<int>>& matrix, int target, 
                           int top, int left, int bottom, int right) {
    //search if the target is inside the rectangular matrix[top:bottom][left:right]
    //each time we discard 1/4 of all elements
    //T(Q) = T(Q/2) + T(Q/4) + O(1) : Drop 1/4 elements + invoke 2 recursive call T(Q/2)
    if(top>bottom || left>right)
        return false;
    
    int x = (top+bottom)/2;
    int y = (left+right)/2;
    int center = matrix[x][y];
    
    if(center > target) {
        return
            searchRect(matrix,target,top,left,x-1,right) ||
            searchRect(matrix,target,x,left,bottom,y-1);
    } else if(center < target){
        return
            searchRect(matrix,target,x+1,left,bottom,right) ||
            searchRect(matrix,target,top,y+1,x,right);
    } else {
        return true;
    }
}


//################################## O(m logn) ################################## 
bool searchMatrix(vector<vector<int>>& matrix, int target) { 
  if(matrix.empty() || matrix.front().empty()) {
    return false;
  } 
  return searchMatrix(matrix, target, 0, matrix.size() - 1); 
}

bool searchMatrix(vector<vector<int>>& matrix, int target, int top, int bottom) { 
  if (top > bottom) { 
    return false; 
  } 
  int mid = top + (bottom - top) / 2;
  if (matrix[mid].front() <= target && target <= matrix[mid].back())
  if (searchVector(matrix[mid], target)) return true;
  if (searchMatrix(matrix, target, top, mid - 1)) return true;
  if (searchMatrix(matrix, target, mid + 1, bottom)) return true;
  return false; 
}

bool searchVector(vector<int>& v, int target) {
  int left = 0, right = v.size() - 1;
  while (left <= right) {
  	int mid = left + (right - left) / 2;
  	if (v[mid] == target)
  		return true;
  	if (v[mid] < target)
  		left = mid + 1;
  	else
  		right = mid - 1;
  }
  return false; 
}
