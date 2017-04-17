//Maximal Rectangle
//Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.
//For example, given the following matrix:
//1 0 1 0 0
//1 0 1 1 1
//1 1 1 1 1
//1 0 0 1 0
//Return 6.



https://discuss.leetcode.com/topic/6650/share-my-dp-solution/57
//maintain a row length of Integer array H recorded its height of '1's, and scan and update row by row to find out the largest rectangle of each row.
//For each row, if matrix[row][i] == '1'. H[i] +=1, or reset the H[i] to zero.
//and accroding the algorithm of [Largest Rectangle in Histogram], to update the maximum area.

public class Solution {
    public int maximalRectangle(char[][] matrix) {
        if (matrix==null||matrix.length==0||matrix[0].length==0)
            return 0;
        int cLen = matrix[0].length;    // column length
        int rLen = matrix.length;       // row length
        // height array 
        int[] h = new int[cLen+1];
        h[cLen]=0;
        int max = 0;
        
        
        for (int row=0;row<rLen;row++) {
            Stack<Integer> s = new Stack<Integer>();
            for (int i=0;i<cLen+1;i++) {
                if (i<cLen)
                    if(matrix[row][i]=='1')
                        h[i]+=1;
                    else h[i]=0;
                
                if (s.isEmpty()||h[s.peek()]<=h[i])
                    s.push(i);
                else {
                    while(!s.isEmpty()&&h[i]<h[s.peek()]){
                        int top = s.pop();
                        int area = h[top]*(s.isEmpty()?i:(i-s.peek()-1));
                        if (area>max)
                            max = area;
                    }
                    s.push(i);
                }
            }
        }
        return max;
    }
}

int maximalRectangle(vector<vector<char> > &matrix) {
    if (matrix.size() <= 0 || matrix[0].size() <= 0)
        return 0;
        
    int m = matrix.size();
    int n = matrix[0].size() + 1;
    int h = 0, w = 0, ret = 0;
    vector<int> height(n, 0);
    
    for (int i = 0; i < m; ++i) {
        stack<int> s;
        for (int j = 0; j < n; ++j) {
            // set value
            if (j < n - 1) {
                if (matrix[i][j] == '1') height[j] += 1;
                else height[j] = 0;
            }
            
            // compute area
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

//############################################### ######################################################
int maximalRectangle(vector<vector<char>>& matrix) { 
  /** largest rectangle based solution **/
  if(matrix.size()<=0 || matrix[0].size()<=0)
      return 0;
  int m=matrix.size();
  int n=matrix[0].size()+1;
  int h=0, w=0, result=0;
  vector<int> height(n, 0);
  for(int i=0; i<m; i++){
      stack<int> s;
      for(int j=0; j<n; j++){
          /** update the current row ended height array **/
          if(j<n-1){
              if(matrix[i][j]=='1')  height[j]+=1;
              else height[j]=0;
          }
          /** use the histogram-max-rectangle-module **/
          while(!s.empty() && height[s.top()]>=height[j]){
              h=height[s.top()];
              s.pop();
              w=s.empty() ? j:j-s.top()-1;
              if(h*w>result) result=h*w;
          }
          s.push(j);
      }
  }
  return result; 
}


//left[j] for j=0..n   means:for current pos j the left consecutive "1" length of row [0...i]
//right[j] for j=0..n   means:for current pos j the right consecutive "1" length of row [0...i]
int maximalRectangle(vector<vector<char>>& matrix) { 
  if(matrix.empty()) return 0;
  const int m = matrix.size();
  const int n = matrix[0].size();
  vector<int> left(n,0), right(n,n), height(n,0);
  int result=0;
  for(int i=0; i<m; i++){ 
    int cur_left=0, cur_right=n; 
    for(int j=0; j<n; j++){
        if(matrix[i][j]=='1') 
          height[j]++; 
        else height[j]=0; //record consective max height
    }
    for(int j=0; j<n; j++){
        if(matrix[i][j]=='1') left[j]= max(left[j], cur_left); //update left
        else  { left[j]=0; cur_left=j+1; }
    }
    for(int j=n-1; j>=0; j--){
        if(matrix[i][j]=='1') right[j]=min(right[j], cur_right);
        else  { right[j]=n; cur_right=j; } //update right
    }
    for(int j=0; j<n; j++){
        result=max(result, (right[j]-left[j])*height[j]); //
    }
  }
  return result; 
}


The DP solution proceeds row by row, starting from the first row. Let the maximal rectangle area at row i and column j be computed by [right(i,j) - left(i,j)]*height(i,j).

All the 3 variables left, right, and height can be determined by the information from previous row, and also information from the current row. So it can be regarded as a DP solution. The transition equations are:

left(i,j) = max(left(i-1,j), cur_left), cur_left can be determined from the current row
right(i,j) = min(right(i-1,j), cur_right), cur_right can be determined from the current row
height(i,j) = height(i-1,j) + 1, if matrix[i][j]=='1';
height(i,j) = 0, if matrix[i][j]=='0'
The code is as below. The loops can be combined for speed but I separate them for more clarity of the algorithm.

class Solution {public:
int maximalRectangle(vector<vector<char> > &matrix) {
    if(matrix.empty()) return 0;
    const int m = matrix.size();
    const int n = matrix[0].size();
    int left[n], right[n], height[n];
    fill_n(left,n,0); fill_n(right,n,n); fill_n(height,n,0);
    int maxA = 0;
    for(int i=0; i<m; i++) {
        int cur_left=0, cur_right=n; 
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
            else {right[j]=n; cur_right=j;}    
        }
        // compute the area of rectangle (can do this from either side)
        for(int j=0; j<n; j++)
            maxA = max(maxA,(right[j]-left[j])*height[j]);
    }
    return maxA;
}
};

If you think this algorithm is not easy to understand, you can try this example:

0 0 0 1 0 0 0 
0 0 1 1 1 0 0 
0 1 1 1 1 1 0
The vector "left" and "right" from row 0 to row 2 are as follows

row 0:

l: 0 0 0 3 0 0 0
r: 7 7 7 4 7 7 7
row 1:

l: 0 0 2 3 2 0 0
r: 7 7 5 4 5 7 7 
row 2:

l: 0 1 2 3 2 1 0
r: 7 6 5 4 5 6 7
The vector "left" is computing the left boundary. Take (i,j)=(1,3) for example. On current row 1, the left boundary is at j=2. However, because matrix[1][3] is 1, you need to consider the left boundary on previous row as well, which is 3. So the real left boundary at (1,3) is 3.

I hope this additional explanation makes things clearer.
