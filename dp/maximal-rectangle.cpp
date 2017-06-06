//Maximal Rectangle
//Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.
//For example, given the following matrix:
//1 0 1 0 0
//1 0 1 1 1
//1 1 1 1 1
//1 0 0 1 0
//Return 6.
//
//############################################ stack   ################################  
//maintain a row length of Integer array H recorded its height of '1's, and scan and update row by row to find out the largest rectangle of each row.
//For each row, if matrix[row][i] == '1'. H[i] +=1, or reset the H[i] to zero.
//and accroding the algorithm of [Largest Rectangle in Histogram], to update the maximum area.
int maximalRectangle(vector<vector<char> > &matrix) {
    if(matrix.empty()) {
        return 0;
    }
    int m = matrix.size();
    int n = matrix[0].size() + 1;
    int h = 0, w = 0, ret = 0;
    vector<int> height(n, 0);
    for (int i = 0; i < m; ++i) {
        stack<int> s; //to maintain width
        for (int j = 0; j < n; ++j) {
            // set value
            /** update the current row ended height array **/
            if (j < n - 1) {
                if (matrix[i][j] == '1') height[j] += 1;
                else height[j] = 0;
            }
            // compute area
            /** use the histogram-max-rectangle-module **/
            while (!s.empty() && height[s.top()] >= height[j]) {
                h = height[s.top()];
                s.pop();
                w = s.empty() ? j : j - s.top() - 1;
                if (h * w > ret) ret = h * w;
            }
            s.push(j);
        }
    }
    return ret;
}

//################################################### DP  ################################################### 
//height counts the number of successive '1's above (plus the current one). 
//The value of left & right means the boundaries of the rectangle which contains the current point with a height of value height.
//
//
matrix
0 0 0 1 0 0 0
0 0 1 1 1 0 0
0 1 1 1 1 1 0

//0th row: 0 0 0 1 0 0 0
//height: 0 0 0 1 0 0 0
//left: 0 0 0 3 0 0 0
//right 7 7 7 4 7 7 7
//
//1st row: 0 0 1 1 1 0 0
//height: 0 0 1 2 1 0 0 
//left: 0 0 2 3 2 0 0
//right: 7 7 5 4 5 7 7
//
//2nd row: 0 1 1 1 1 1 0
//height: 0 1 2 3 2 1 0
//left: 0 1 2 3 2 1 0
//right: 7 6 5 4 5 6 7
//
//

//0  0  0  1  0  0  0
//
//0  0  1  1  1  0  0
//
//0  1  1  1  1  1  0
//
//#the 1th row: calculate the are from left to right which enclosed by '*'
//        ***
//0  0  0 *1* 0  0  0
//        ***
//0  0  1  1  1  0  0
//
//0  1  1  1  1  1  0
//
//#the 2th row: calculate the are from left to right
//1th area:                      2th area:
//                                       ***
//0  0  0  1  0  0  0            0  0  0 *1* 0  0  0
//     *********                         * *      
//0  0 *1  1  1* 0  0            0  0  1 *1* 1  0  0
//     *********                         ***            
//0  1  1  1  1  1  0            0  1  1  1  1  1  0
//
//3th area: 
//                                   
//0  0  0  1  0  0  0            
//     *********                               
//0  0 *1  1  1* 0  0           
//     ********* 
//0  1  1  1  1  1  0   
//
//#the 3th row: calculate the are from left to right
//1th area:                      2th area:                
//
//0  0  0  1  0  0  0            0  0  0  1  0  0  0   
//                                    *********
//0  0  1  1  1  0  0            0  0 *1  1  1* 0  0
//  ***************                   *       *
//0 *1  1  1  1  1* 0            0  1 *1  1  1* 1  0
//  ***************                   *********
//3th area:                      4th area:                
//        ***
//0  0  0 *1* 0  0  0            0  0  0  1  0  0  0   
//        * *                         *********
//0  0  1 *1* 1  0  0            0  0 *1  1  1* 0  0
//        * *                         *       *
//0  1  1 *1* 1  1  0            0  1 *1  1  1* 1  0
//        ***                         *********
//5th area:                                     
//
//0  0  0  1  0  0  0          
//                                   
//0  0  1  1  1  0  0         
//  ***************               
//0 *1  1  1  1  1* 0          
//  ***************           

int maximalRectangle(vector<vector<char>>& matrix) {
  if(matrix.empty()) return 0;
  const int m = matrix.size();
  const int n = matrix[0].size();
  int left[n], right[n], height[n];
  fill_n(left,n,0); fill_n(right,n,n); fill_n(height,n,0);
  int maxA = 0;
  for(int i=0; i<m; i++) {
      int cur_left=0, cur_right=n-1; 
      for(int j=0; j<n; j++) { // compute height (can do this from either side)
          if(matrix[i][j]=='1') height[j]++; 
          else height[j]=0;
      }
      for(int j=0; j<n; j++) { // compute left (from left to right)
          if(matrix[i][j]=='1') left[j]=max(left[j],cur_left);
          else {left[j]=0; cur_left=j+1;}
      }
      // compute right (from right to left)
      for(int j=n-1; j>=0; j--) {
          if(matrix[i][j]=='1') right[j]=min(right[j],cur_right);
          else {right[j]=n-1; cur_right=j-1;}    
      }
      // compute the area of rectangle (can do this from either side)
      for(int j=0; j<n; j++)
          maxA = max(maxA,(right[j]-left[j]+1)*height[j]);
  }
  return maxA;
}


//######################################## pytonic  ######################################## 
//def maximalRectangle(self, matrix):
//    if not matrix or not matrix[0]:
//        return 0
//    n = len(matrix[0])
//    height = [0] * (n + 1)
//    ans = 0
//    for row in matrix:
//        for i in xrange(n):
//            height[i] = height[i] + 1 if row[i] == '1' else 0
//        stack = [-1]
//        for i in xrange(n + 1):
//            while height[i] < height[stack[-1]]:
//                h = height[stack.pop()]
//                w = i - 1 - stack[-1]
//                ans = max(ans, h * w)
//            stack.append(i)
//    return ans
//
//The solution is based on largest rectangle in histogram solution. Every row in the matrix is viewed as the ground with some buildings on it. The building height is the count of consecutive 1s from that row to above rows. The rest is then the same as this solution for largest rectangle in histogram
