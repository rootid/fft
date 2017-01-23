//Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.
//For example,
//Given n = 3,
//You should return the following matrix:
//[
// [ 1, 2, 3 ],
// [ 8, 9, 4 ],
// [ 7, 6, 5 ]
//]

#include "../headers/global.hpp"

vector<vector<int> > generateMatrix(int n) {
      vector<vector <int> > rv(n,vector<int>(n));
      int rowMin = 0;
      int rowMax = n-1;
      int colMin = 0;
      int colMax = n-1;
      int idx = 1;
      while (rowMin <= rowMax && colMin <= colMax) {
          for(int i=colMin;i<=colMax;i++) {  //l->r
              rv[rowMin][i] = idx++;
          }
          rowMin += 1;
          for(int i=rowMin;i<=rowMax;i++) {  //u->d
              rv[i][colMax] = idx++;
          }
          colMax -= 1;
          if(rowMin <= rowMax) {  // [ [2,3] ]
            for(int i=colMax;i>=colMin;i--) {  //r->l
                rv[rowMax][i] = idx++;
            }
          }
          rowMax -= 1;
          if(colMin <= colMax) {
            for(int i=rowMax;i>=rowMin;i--) {   //d->u
                rv[i][colMin] = idx++;
            }
          }
          colMin +=1;
          
      }
      return rv;
}

// More readable version
//int num = 1, rowbegin = 0, rowend = n - 1, colbegin = 0, colend = n - 1;
//      while (rowbegin <= rowend && colbegin <= colend) {
//          for (int i = colbegin; i <= colend; i++) matrix[rowbegin][i] = num++;
//          rowbegin++;
//          
//          for (int i = rowbegin; i <= rowend; i++) matrix[i][colend] = num++;
//          colend--;
//          
//          for (int i = colend; i >= colbegin; i--) matrix[rowend][i] = num++;
//          rowend--;
//          
//          for (int i = rowend; i >= rowbegin; i--) matrix[i][colbegin] = num++;
//          colbegin++;
//      }

int main() {

}
