//You are given an n x n 2D matrix representing an image.
//Rotate the image by 90 degrees (clockwise).
//Follow up:
//Could you do this in-place?

#include "../headers/global.hpp"
void rotate(vector<vector<int>>& matrix) {
      int m = matrix.size();
       for(int i=m-1;i>=0;i--) {
         int x = i;
         int y = m-1-i;
         //cout << " (x,y) " << x << "," << y << endl;
         int step_x = 0;
         int step_y = 0;
         while (x+step_x  >= 0  && y+step_y  < m ) {
            //cout << " [x,y] = " << x+step_x  << "," << y << " ( " << x << "," << y+step_y << ")" << endl;
            swap(matrix[x+step_x][y],matrix[x][y+step_y]);
            step_x--;
            step_y++;
         }
      }
      for(int j=0;j<m/2;j++) {
          swap(matrix[j],matrix[m-1-j]);
      }
}
int main() {
 int a[] = {1,2,3};
 int b[] = {4,5,6};
 int c[] = {7,8,9};
 vector<vector<int> > av;
 vector<int> bv (a,a+sizeof(a)/sizeof(a[0])) ;
 vector<int> bv1 (b,b+sizeof(b)/sizeof(b[0])) ;
 vector<int> bv2 (c,c+sizeof(c)/sizeof(c[0])) ;
 av.push_back(bv);
 av.push_back(bv1);
 av.push_back(bv2);
 rotate(av);
}
