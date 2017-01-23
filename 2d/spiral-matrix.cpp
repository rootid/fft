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

//with 2 indexes
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

//with 4 indexes
vector<int> spiralOrder(vector<vector<int>>& matrix) {
       vector<int> res;
       int m = matrix.size();
       if(m == 0) {
           return res;
       }
       int n = matrix[0].size();
       int rowMin = 0;
       int rowMax = m-1;
       int colMin = 0;
       int colMax = n-1;
       while (rowMin <= rowMax && colMin <= colMax) {
           for(int i=colMin;i<=colMax;i++) {  //l->r
               res.push_back(matrix[rowMin][i]);
           }
           rowMin += 1;
           for(int i=rowMin;i<=rowMax;i++) {  //u->d
               res.push_back(matrix[i][colMax]);
           }
           colMax -= 1;
           if(rowMin <= rowMax) {  // [ [2,3] ]
             for(int i=colMax;i>=colMin;i--) {  //r->l
                 res.push_back(matrix[rowMax][i]);
             }
           }
           rowMax -= 1;
           if(colMin <= colMax) {
             for(int i=rowMax;i>=rowMin;i--) {   //d->u
                 res.push_back(matrix[i][colMin]);
             }
           }
           colMin +=1;
           
       }
      return res;    
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
