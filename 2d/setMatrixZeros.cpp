//Set Matrix Zeroes
//Given a m x n matrix, if an element is 0, set its entire row and column to 0.
//Do it in place.
//
//Follow up:
//Did you use extra space?
//A straight forward solution using O(mn) space is probably a bad idea.
//A simple improvement uses O(m + n) space, but still not the best solution.
//Could you devise a constant space solution?

#include<iostream>
#include<vector>
using namespace std;

void setZeroes(vector<vector<int>>& matrix) {

  int m = matrix.size();
  int n = matrix[0].size();
  bool isRowZero = false;
  bool iscolZero = false;
  for(int i=0;i<m;i++) {
    if(matrix[i][0] == 0) {
      isRowZero = true;
    }
  }

  for(int j=0;j<n;j++) {
    if(matrix[0][j] == 0) {
      isColZero = true;
    }
  }
  for(int i=1;i<m;i++) {
    for(int j=1;j<n;j++) {
      if(matrix[i][0] == 0 && matrix[0][j]) {
        continue;     // avoid repeated checks
      }
      if(matrix[i][j] == 0) {
        matrix[i][0] = 0;
        matrix[0][j] = 0;
      }
    }
  }

  for(int i=1;i<m;i++) {
    int j = 0;
    if(matrix[i][0] == 0) {
      while(j < n) {
        matrix[i][j] = 0;
        j++;
      }
    }
  }

  for(int j=1;j<n;j++) {
    int i = 0;
    if(matrix[0][j] == 0) {
      while(i < m) {
        matrix[i][j] = 0;
        i++;
      }
    }
  }

  if(isRowZero) {
    int i =0;
    while(i < m) {
      matrix[i][0] = 0;
      i++;
    }
  }

  if(isColZero) {
    int j =0;
    while(j < n) {
      matrix[0][j] = 0;
      j++;
    }
  }

}

int main() {

}
