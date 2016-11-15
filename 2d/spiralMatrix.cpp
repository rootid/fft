//Spiral Matrix

//Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.
//For example,
//Given the following matrix:
//[
// [ 1, 2, 3 ],
// [ 4, 5, 6 ],
// [ 7, 8, 9 ]
//]
//You should return [1,2,3,6,9,8,7,4,5].

#include<iostream>
#include<vector>
using namespace std;


vector<int> spiralOrder(vector<vector<int> >& matrix) {
  int m = matrix.size();
  int n = matrix[0].size();
  
  int col = -1;
  int row = 0;
  while (row != col) {
    while(col < n) {
      col++;
      cout << matrix[row][col] << " ";
    }
    //n = n-1;
    n--;
    while(row < m) {
      row++;
      cout << matrix[row][col] << " ";
    }
    //m -= 1;
    m--;
    col -= 1;
    while(col >= 0) {
      col--;
      cout << matrix[row][col] << " ";
    }
    row = row - 1;
    while(row < m) {
      row++;
      cout << matrix[row][col] << " ";
    }
  }
}

int main() {

 // vector<vector<int> > av (3,vector<int>(3) );
 // int a[] = {1,2,3};
 // int b[] = {4,5,6};
 // int c[] = {7,8,9};
 // //av[0](a,a+sizeof(a)/sizeof(a[0]) ) ;
 // for(int i=0;i<3;i++) {
 //   av[0][i] = a[i];
 // }
 int a[] = {1};
 vector<vector<int> > av;
 vector<int> bv (a,a+sizeof(a)/sizeof(a[0])) ;
 av.push_back(bv);

 spiralOrder(av);
}
